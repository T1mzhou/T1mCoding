#include "fat32_test.h"
#include "common_types.h"
#include "driver.h"
#include "disk.h"


extern disk_driver_t vdisk_driver;


const char* disk_path_test = "/workspace/FAT32/resources/disk_test.img";
static u32_t write_buffer[24 * 1024];
static u32_t read_buffer[24 * 1024];

static int disk_io_test() {
    int err = 0;
    disk_t disk_test;

    disk_test.driver = &vdisk_driver;

    memset(read_buffer, 0, sizeof(read_buffer));

    err = disk_test.driver->open(&disk_test, (void*)disk_path_test);
    if (err) {
        printf("open disk failed\n");
        return -1;
    }

    err = disk_test.driver->write_sector(&disk_test, (u8_t*)write_buffer, 0, 8);
    if (err) {
        printf("disk write failed\n");
        return -1;
    }

    err = disk_test.driver->read_sector(&disk_test, (u8_t*)read_buffer, 0, 8);
    if (err) {
        printf("disk read failed\n");
        return -1;
    }

    err = memcmp((u8_t*)read_buffer, (u8_t*)write_buffer, disk_test.sector_size * 8);
    if (err) {
        printf("data is not equal\n");
        return -1;
    }

    err = disk_test.driver->close(&disk_test);
    if (err) {
        printf("disk close failed\n");
        return -1;
    }

    printf("disk io test ok\n");
    return 0;
}

int test_disk_io() {
    for (int i = 0; i < sizeof(write_buffer) / sizeof(u32_t); i++) {
        write_buffer[i] = i;
    }

    int err = disk_io_test();
    if (err) return err;

    printf("test End\n");
}