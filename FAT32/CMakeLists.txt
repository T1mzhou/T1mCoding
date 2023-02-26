cmake_minimum_required(VERSION 3.12)
project(FAT32)

set(CMAKE_C_STANDARD 11)

# LINK_LIBRARIES(m pthread)

include_directories("${PROJECT_SOURCE_DIR}/common")
include_directories("${PROJECT_SOURCE_DIR}/disk")
include_directories("${PROJECT_SOURCE_DIR}/driver")
include_directories("${PROJECT_SOURCE_DIR}/fat32_fs")

aux_source_directory(${PROJECT_SOURCE_DIR} DIR_MAIN_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/common DIR_COMMON_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/disk DIR_DISK_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/driver DIR_DRIVER_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/fat32_fs DIR_FAT32_FS_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/test DIR_TEST_SRCS)

add_executable(fat32 ${DIR_MAIN_SRCS} ${DIR_COMMON_SRCS} ${DIR_DISK_SRCS} ${DIR_DRIVER_SRCS} ${DIR_FAT32_FS_SRCS} ${DIR_TEST_SRCS})
