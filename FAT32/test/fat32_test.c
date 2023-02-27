#include "fat32_test.h"
#include "common_types.h"
#include "driver.h"
#include "disk.h"


extern disk_driver_t vdisk_driver;


const char* disk_path_test = "/workspace/FAT32/resources/disk_test.img";
const char* disk_path_img = "/workspace/FAT32/resources/disk.img";
static u32_t write_buffer[24 * 1024];
static u32_t read_buffer[24 * 1024];
disk_t disk;

static int disk_io_test() {
    int err = 0;
    disk_t disk_test;

    memset(read_buffer, 0, sizeof(read_buffer));

    err = disk_open(&disk_test, "vdisk", &vdisk_driver, (void*)disk_path_test);
    if (err) {
        printf("open disk failed\n");
        return -1;
    }

    err = disk_write_sector(&disk_test, (u8_t*)write_buffer, 0, 2);
    if (err) {
        printf("disk write failed\n");
        return -1;
    }

    err = disk_read_sector(&disk_test, (u8_t*)read_buffer, 0, 2);
    if (err) {
        printf("disk read failed\n");
        return -1;
    }

    err = memcmp((u8_t*)read_buffer, (u8_t*)write_buffer, disk_test.sector_size * 2);
    if (err) {
        printf("data is not equal\n");
        return -1;
    }

    err = disk_close(&disk_test);
    if (err) {
        printf("disk close failed\n");
        return -1;
    }

    printf("disk io test ok\n");
    return 0;
}


int disk_part_test() {
    u32_t count;
    efat32_err_t err = FAT32_ERR_OK;

    err = disk_get_part_count(&disk, &count);
    if (err < 0) {
        printf("partion count detect failed\n");
        return err;
    }

    printf("partition count:%d\n", count);
}

int test_disk_io() {
    for (int i = 0; i < sizeof(write_buffer) / sizeof(u32_t); i++) {
        write_buffer[i] = i;
    }

    int err = disk_io_test();
    if (err) return err;

    printf("test End\n");
}



int test_disk_part() {
    efat32_err_t err;

    err = disk_open(&disk, "vdisk", &vdisk_driver, (void*)disk_path_img);
    if (err < 0) {
        return err;
    }

    err = disk_part_test();
    if (err < 0) {
        return err;
    }

    err = disk_close(&disk); 
    if (err < 0) {
        return err;
    }

    printf("Test end\n");   
}