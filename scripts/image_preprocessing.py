#!/usr/bin/env python3
"""
make_image_headers.py

Usage:
    python3 image_preprocessing.py \
      --input-dir /path/to/original_images \
      --out-bin-dir /path/to/output/bin \
      --out-src-dir /path/to/project/src \
      --size 224 224

This script:
 - loads images, applies EXIF rotation, forces RGB
 - resizes to SIZE (default 224x224) using LANCZOS
 - writes raw .bin files (HWC, uint8)
 - writes a pair of files for each image: src/<base>_image.cc and src/<base>_image.h
   * .h contains extern declarations (C compatible)
   * .cc contains const unsigned char array and const unsigned int length
 - verifies that the .bin bytes equal the Pillow-produced bytes
"""
import os
import argparse
from PIL import Image, ImageOps
import numpy as np
import re
import tempfile

def sanitize_varname(s: str) -> str:
    # Create a C identifier from base filename
    s = re.sub(r'[^0-9a-zA-Z_]', '_', s)
    if re.match(r'^[0-9]', s):
        s = '_' + s
    return s

def atomic_write(path: str, data: bytes):
    d = os.path.dirname(path) or '.'
    with tempfile.NamedTemporaryFile(dir=d, delete=False) as tf:
        tf.write(data)
        tmp = tf.name
    os.replace(tmp, path)

def process_image(img_path: str, target_size=(224,224)):
    img = Image.open(img_path)
    img = ImageOps.exif_transpose(img)
    img = img.convert('RGB')
    img = img.resize(target_size, Image.LANCZOS)
    arr = np.asarray(img, dtype=np.uint8)  # shape (H,W,3)
    if arr.ndim != 3 or arr.shape[2] != 3:
        raise RuntimeError(f"Image not RGB after conversion: {img_path} -> shape {arr.shape}")
    return img, arr

def write_bin(bin_path: str, arr: np.ndarray):
    # arr is HWC uint8
    atomic_write(bin_path, arr.tobytes())

def write_cc_h(bin_path: str, out_cc: str, out_h: str, varname: str):
    data = open(bin_path, 'rb').read()
    n = len(data)

    # Header (extern declarations)
    header_text = f"""#pragma once
#ifdef __cplusplus
extern "C" {{
#endif

extern const unsigned char {varname}[];
extern const unsigned int {varname}_len;

#ifdef __cplusplus
}}
#endif
"""
    atomic_write(out_h, header_text.encode('utf-8'))

    # CC - include header and define const array
    # We'll format 12 bytes per line
    lines = []
    lines.append(f'#include "{os.path.basename(out_h)}"\n\n')
    lines.append(f'const unsigned int {varname}_len = {n};\n')
    lines.append(f'alignas(16) const unsigned char {varname}[] = {{\n')
    for i in range(0, n, 12):
        chunk = data[i:i+12]
        line = '  ' + ', '.join(f'0x{b:02x}' for b in chunk) + ',\n'
        lines.append(line)
    lines.append('};\n')
    cc_text = ''.join(lines)
    atomic_write(out_cc, cc_text.encode('utf-8'))

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--input-dir', required=True)
    p.add_argument('--out-bin-dir', required=True)
    p.add_argument('--out-src-dir', required=True, help="where .cc/.h will be written (e.g. project/src)")
    p.add_argument('--size', nargs=2, type=int, default=[224,224], help="width height")
    p.add_argument('--pattern', default='*.jpg', help="glob pattern for input images (info only)")
    args = p.parse_args()

    input_dir = os.path.abspath(args.input_dir)
    out_bin_dir = os.path.abspath(args.out_bin_dir)
    out_src_dir = os.path.abspath(args.out_src_dir)


    target_size = (args.size[0], args.size[1])
    expected_bytes = target_size[0] * target_size[1] * 3

    filenames = sorted([f for f in os.listdir(input_dir) if f.lower().endswith(('.jpg','.jpeg','.png'))])
    if not filenames:
        print("No images found in", input_dir)
        return

    for fname in filenames:
        base = os.path.splitext(fname)[0]
        print("Processing", fname, "-> base:", base)
        in_path = os.path.join(input_dir, fname)

        img, arr = process_image(in_path, target_size=target_size)

        if arr.nbytes != expected_bytes:
            raise RuntimeError(f"Unexpected byte-size {arr.nbytes} != expected {expected_bytes}")

        # write bin
        bin_path = os.path.join(out_bin_dir, f"{base}.bin")
        write_bin(bin_path, arr)
        print(" Wrote bin:", bin_path)

        # validate bin equals pillow bytes
        bin_bytes = open(bin_path, 'rb').read()
        if bin_bytes != arr.tobytes():
            raise RuntimeError("Bin mismatch for " + fname)

        # write cc and h
        varname = sanitize_varname(base + '_image')
        out_cc = os.path.join(out_src_dir, f"{varname}.cc")
        out_h  = os.path.join(out_src_dir, f"{varname}.h")
        write_cc_h(bin_path, out_cc, out_h, varname)
        print(" Wrote:", out_cc, out_h)
        print(" First 10 bytes:", list(bin_bytes[:10]))

    print("All done with generated headers")

if __name__ == '__main__':
    main()
