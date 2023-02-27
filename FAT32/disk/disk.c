#include "disk.h"
#include <stdio.h>

u8_t temp_buffer[512];

efat32_err_t disk_open(disk_t* disk, const char* name, disk_driver_t* driver, void* init_data) {
    efat32_err_t err;
    disk->driver = driver;

    err = disk->driver->open(disk, init_data);
    if (err < 0) {
        return err;
    }

    disk->name = name;

    return FAT32_ERR_OK;
}


efat32_err_t disk_close(disk_t* disk) {
    efat32_err_t err;

    err = disk->driver->close(disk);
   
    return err;
}

efat32_err_t disk_read_sector(disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count) {
    efat32_err_t err;

    if (start_sector * count >= disk->total_sector) {
        return FAT32_ERR_PARAM;
    }
    
    err =  disk->driver->read_sector(disk, buffer, start_sector, count);

    return err;
}

efat32_err_t disk_write_sector(disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count) {
    efat32_err_t err;

    err =  disk->driver->write_sector(disk, buffer, start_sector, count);
   

    return err;
}

efat32_err_t disk_get_part_count(disk_t *disk, u32_t *count) {
    int read_count = 0;
    efat32_err_t err;
    mbr_part_t* part;
    u8_t* buffer = temp_buffer;

    // 读取头部信息512个字节 mbr
    err = disk_read_sector(disk, buffer, 0, 1);
    if (err < 0) {
        return err;
    }

    part = ((mbr_t*)buffer)->part_info;
    for (int i = 0; i < MBR_PRIMARY_PART_NR; i++, part++) {
        if (part->system_id == FS_NOT_VALID) {
            continue;
        } else {
            read_count++;
        }
    }

    *count = read_count;
    return FAT32_ERR_OK;
}