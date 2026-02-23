//C program that illustrates files locking goes here
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    struct flock lock;

    fd = open("lockfile.txt", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        perror("Open failed");
        exit(1);
    }

    // Initialize lock structure
    lock.l_type = F_WRLCK;     // Write lock
    lock.l_whence = SEEK_SET;  // From beginning
    lock.l_start = 0;          // Start offset
    lock.l_len = 0;            // Lock whole file

    printf("Trying to acquire lock...\n");

    // Apply lock
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Lock failed");
        close(fd);
        exit(1);
    }

    printf("Lock acquired. Press Enter to release lock...\n");
    getchar();

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    printf("Lock released.\n");

    close(fd);

    return 0;
}
