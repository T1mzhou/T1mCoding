#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

#include <stdint.h>

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;

typedef enum _efat32_err_t {
    FAT32_ERR_OK = 0,
    FAT32_ERR_IO = -1,
    FAT32_ERR_NULLPTR = -2,
    FAT32_ERR_PARAM = -3,
} efat32_err_t;


#endif // end of __COMMON_TYPES_H__