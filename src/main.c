#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/sys/printk.h>
#include "image.h"  // Include the generated image header
#include <zephyr/logging/log.h>

// Flash memory addresses (sumfwna me to datasheet kai to dts)
#define FLASH0_BASE_ADDR 0x02000000  // Secure access to Code Flash
#define FLASH1_BASE_ADDR 0x27000000  // Secure access to Data Flash

//Logging
LOG_MODULE_REGISTER(thesis_project);

/*Save the image into flash0 and flash1 of the Renesas ek_ra8d1 board. To grafw kai sta duo flash pros to parwn alla tha xreiastw mono ena argotera.*/



int main(void)
{
    const struct device *flash_dev;  //pernei apo to dts automata ta correct variables.
    int ret=0;

    // Get the flash device binding from the dts tree.
    flash_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_flash_controller));
    if (!device_is_ready(flash_dev)) {
        printk("Flash device not ready\n");
        return;
    }

    printk("Flash device ready\n");

    // Write image to Code Flash Memory (flash0)
    ret = flash_write(flash_dev, FLASH0_BASE_ADDR, image_jpeg, image_jpeg_len);
    if (ret != 0) {
        printk("Failed to write to Code Flash: %d\n", ret);
    } else {
        printk("Image written to Code Flash at address 0x%x\n", FLASH0_BASE_ADDR);
    }

    // Write image to Data Flash Memory (flash1)
    ret = flash_write(flash_dev, FLASH1_BASE_ADDR, image_jpeg, image_jpeg_len);
    if (ret != 0) {
        printk("Failed to write to Data Flash: %d\n", ret);
    } else {
        printk("Image written to Data Flash at address 0x%x\n", FLASH1_BASE_ADDR);
    }

    // Verify the written data
    uint8_t read_buffer[image_jpeg_len];
    ret = flash_read(flash_dev, FLASH0_BASE_ADDR, read_buffer, image_jpeg_len);
    if (ret != 0) {
        printk("Failed to read from Code Flash: %d\n", ret);
    } else if (memcmp(image_jpeg, read_buffer, image_jpeg_len) == 0) {
        printk("Code Flash verification successful\n");
    } else {
        printk("Code Flash verification failed\n");
    }

    ret = flash_read(flash_dev, FLASH1_BASE_ADDR, read_buffer, image_jpeg_len);
    if (ret != 0) {
        printk("Failed to read from Data Flash: %d\n", ret);
    } else if (memcmp(image_jpeg, read_buffer, image_jpeg_len) == 0) {
        printk("Data Flash verification successful\n");
    } else {
        printk("Data Flash verification failed\n");
    }
return 0;
}