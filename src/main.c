#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <string.h>
#include "image.h"


LOG_MODULE_REGISTER(thesis_project);

/* mporw na valw kai DMA sto mellon mias kai to ypostirizei to zephyr*/

#define SRAM1_BASE_ADDR 0x22060000  // Secure alias (or 0x32060000 for non-secure) sumfwna me to memory mapping.
#define SRAM1_SIZE      512 * 1024   // 512KB

/* Pointer to SRAM1 */
volatile uint8_t * const sram1 = (uint8_t *)SRAM1_BASE_ADDR;  //volatile giati o pointer mporei na allaksei thesi.

int main(void)
{
    /* ver so that image fits in SRAM */
    if (sizeof(image_jpeg) > SRAM1_SIZE) {
        LOG_ERR("Image too large for SRAM1!");
        return -ENOMEM;
    }

    /* Apeuthias. memory copy stin RAM xwris na xreiazetai erase opws stin flash mnimi */
    memcpy((void *)sram1, image_jpeg, sizeof(image_jpeg));  //me pointer doulevei ousiastika mono.

    if (memcmp(image_jpeg, (void *)sram1, sizeof(image_jpeg)) == 0) {
        LOG_INF("SRAM write successful!");
        LOG_INF("Image copied to 0x%08x, size %zu bytes", 
               SRAM1_BASE_ADDR, sizeof(image_jpeg));
    } else {
        LOG_ERR("SRAM verification failed!");
        return -EIO;
    }
      
    bool verify = memcmp(image_jpeg, (void *)SRAM1_BASE_ADDR, sizeof(image_jpeg)) == 0;
    LOG_INF("SRAM verification: %s", verify ? "PASSED" : "FAILED");

    /* Hex dump first 32 bytes kai verification */
    LOG_INF("First 32 bytes:");
    for (int i = 0; i < 32; i++) {
        printk("%02x ", ((uint8_t *)SRAM1_BASE_ADDR)[i]);
        if ((i+1) % 16 == 0) printk("\n"); //gia allagh grammis apla.
    }

    return 0;
}
