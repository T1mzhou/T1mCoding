#ifndef __DISK_H__
#define __DISK_H__

#include "common_types.h"

#define MBR_PRIMARY_PART_NR (4)

/*
* 文件系统类型
*/
typedef enum {
    FS_NOT_VALID = 0x00,        // 无效类型
    FS_FAT32 =  0x01,           // FAT32
    FS_EXTEND = 0x05,           // 拓展分区
    FS_WIN95_FAT32_0 = 0xB,     // FAT32
    FS_WIN95_FAT32_1 = 0xC,     // FAT32
}efs_type_t;

#pragma pack(1)
/*
 * MBR的分区表项类型
 *
*/
typedef struct _mbr_part_t{
    u8_t    boot_active;            // 分区是否活动
    u8_t    start_header;           // 起始header
    u16_t   start_cycliner : 10;    // 起始磁道
    u8_t    system_id;              // 文件系统类型
    u8_t    end_header;             // 结束header
    u16_t    end_sector : 6;        // 结束扇区
    u16_t    end_cyliner : 10;      // 结束磁道
    u32_t    relative_sectors;      // 相对于该驱动器开始的相对扇区数
    u32_t    total_sector;          // 总的扇区数
}mbr_part_t;

/*
* MBR区域描述结构
*/
typedef struct _mbr_t {
    u8_t code[446];         // 引导代码区
    mbr_part_t part_info[MBR_PRIMARY_PART_NR];
    u8_t boot_sig[2];       // 引导标志 
}mbr_t;

#pragma pack()

struct _disk_t;

/*
* 磁盘驱动接口
*/
typedef struct _disk_driver_t {
    efat32_err_t (*open)(struct _disk_t* disk, void* init_data);
    efat32_err_t (*close)(struct _disk_t* disk);
    efat32_err_t (*read_sector)(struct _disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
    efat32_err_t (*write_sector)(struct _disk_t* disk,u8_t* buffer, u32_t start_sector, u32_t count);
}disk_driver_t;

/*
* 存储设备类型
*/
typedef  struct _disk_t {
    const char* name;
    u32_t sector_size;              /* 扇区大小 */
    u32_t total_sector;             /* 扇区总数 */
    disk_driver_t* driver;          /* 驱动抽象接口 */
    void* data;                     /* 通用数据指针 */
} disk_t;

efat32_err_t disk_open(disk_t* disk, const char* name, disk_driver_t* driver, void* init_data);    
efat32_err_t disk_close(disk_t* disk);  
efat32_err_t disk_get_part_count(disk_t *disk, u32_t *count);  
efat32_err_t disk_read_sector(disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
efat32_err_t disk_write_sector(disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);


#endif // end of  __DISK_H__
