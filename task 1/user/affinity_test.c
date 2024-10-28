#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int mask = 5;
    set_affinity_mask(mask);  // Call the system call to set the CPU affinity mask

    for (int i = 0; i < 10; i++)
    {
        printf("Running on PID: %d ", getpid());
        sleep(1); // Sleep for a while to make the output readable
    }
    

    return 0;
}