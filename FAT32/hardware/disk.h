#ifndef __DISK_H__
#define __DISK_H__

#include "common_types.h"

struct _disk_t;

typedef struct _disk_driver_t {
    efat32_err_t (*open)(struct _disk_t* disk, void* init_data);
    efat32_err_t (*close)(struct _disk_t* disk);
    efat32_err_t (*read_sector)(struct _disk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
    efat32_err_t (*write_sector)(struct _disk_t* disk,u8_t* buffer, u32_t start_sector, u32_t count);
}disk_driver_t;

typedef  struct _disk_t {
    u32_t sector_size;              /* 扇区大小 */
    u32_t total_sector;             /* 扇区总数 */
    disk_driver_t* driver;          /* 驱动抽象接口 */
    void* data;                     /* 通用数据指针 */
} disk_t;

void disk_test();

#endif // end of  __DISK_H__
