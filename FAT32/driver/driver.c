#include <stdio.h>
#include "common_types.h"
#include "driver.h"
#include "disk.h"
 
static efat32_err_t disk_hw_open(struct _disk_t* disk, void* init_data) {
    const char* path = (const char*)init_data;
    
    FILE* file = fopen(path, "rb+");
    if (file == NULL) {
        printf("open disk failed:%s\n", path);
        return FAT32_ERR_IO;
    }   

    disk->data = file;
    disk->sector_size = 512; // 大于255有问题 ‘int’ to ‘u32_t’ {aka ‘unsigned char’} changes value from ‘256’ to ‘0’ 搞成uin8_t导致
    
    fseek(file, 0, SEEK_END);
    disk->total_sector = ftell(file) / disk->sector_size;
   
    return FAT32_ERR_OK;
}
    
static efat32_err_t disk_hw_close(struct _disk_t* disk) {
    FILE* file = (FILE*)disk->data;
    fclose(file);

    return FAT32_ERR_OK;
}
    
static efat32_err_t  disk_hw_read_sector(struct _disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count) {
    u32_t offset = start_sector * count;
    FILE* file = (FILE*)disk->data;

    int err = fseek(disk->data, 0, SEEK_SET);
    if (err == -1) {
        printf("seek disk failed: 0x%x\n", offset);
    }

    err = (int)fread(buffer, disk->sector_size, count, file);
    if (err == -1) {
        printf("read disk failed: sector: %d, count: %d\n", start_sector, count);
        return FAT32_ERR_IO;
    }

    return FAT32_ERR_OK;
}

static efat32_err_t  disk_hw_write_sector(struct _disk_t* disk,u8_t* buffer, u32_t start_sector, u32_t count) {
    u32_t offset = start_sector * count;
    FILE* file = (FILE*)disk->data;

    int err = fseek(disk->data, 0, SEEK_SET);
    if (err == -1) {
        printf("seek disk failed: 0x%x\n", offset);
    }

    err = fwrite(buffer, disk->sector_size, count, file);
    if (err == -1) {
        printf("write disk failed: sector: %d, count: %d\n", (int)start_sector,(int)count);
        return FAT32_ERR_IO;
    }

    fflush(file);
    return FAT32_ERR_OK;
}

disk_driver_t vdisk_driver = {
    .open = disk_hw_open,
    .close = disk_hw_close,
    .read_sector = disk_hw_read_sector,
    .write_sector = disk_hw_write_sector,
};