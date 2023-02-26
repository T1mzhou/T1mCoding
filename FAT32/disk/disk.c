#include "disk.h"
#include <stdio.h>

efat32_err_t disk_open(disk_t* disk, const char* name, disk_driver_t* driver, void* init_data) {
    efat32_err_t err;

    const char * path = init_data;
    disk->driver = driver;

    err = disk->driver->open(disk, path);
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