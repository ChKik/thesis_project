from PIL import Image
import os, os.path

resize_width=224
resize_height=224

#checks  to current directory gia number of files.
for x in range(1,len(os.listdir('/home/haris/thesis_project/image_preprocessing'))):
    fd=Image.open(f"{x}.jpeg")
    fd=fd.resize((resize_width,resize_height),Image.LANCZOS)
    print("Resized image")
    print(fd)
    
    base_name=os.path.splitext(fd)[0] #pairnei to onoma toy file mono.
    new_img= fd.save('/home/haris/thesis_project/image_preprocessing',f"{base_name}_resized.jpg",format='JPEG')

