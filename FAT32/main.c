#include <stdio.h>
#include "test/fat32_test.h"


int main(void) {
    printf("main Start\n");
    //test_disk_io();
    test_disk_part();
    printf("main End\n");
    return 0; 
}
