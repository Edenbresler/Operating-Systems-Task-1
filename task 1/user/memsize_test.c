#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    // Print how many bytes of memory the running process is using 
    int memBytes = memsize();
    printf("The running process is using %d bytes of memory\n", memBytes);

    // Allocate 20k more bytes of memory
    int allocateBytes = 20 * 1024; 
    char *buffer = (char *)malloc(allocateBytes);
    if (buffer == 0) {
        printf("Memory allocation failed\n");
        exit(1,0);
    }

    // Print how meny bytes of memory usage after allocation
    int newMemBytes = memsize();
    printf("After allocating, the running process is using: %d bytes\n", newMemBytes);

    // Free the allocated array
    free(buffer);

    // Print how meny bytes of memory usage after releasing the memory
    int afterFreeBytes = memsize();
    printf("After release, the running process is using: %d bytes\n", afterFreeBytes);

    exit(0,0);
}