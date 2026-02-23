# Linux-File-IO-Systems-locking
Ex07-Linux File-IO Systems-locking
# AIM:
To Write a C program that illustrates files copying and locking

# DESIGN STEPS:

### Step 1:

Navigate to any Linux environment installed on the system or installed inside a virtual environment like virtual box/vmware or online linux JSLinux (https://bellard.org/jslinux/vm.html?url=alpine-x86.cfg&mem=192) or docker.

### Step 2:

Write the C Program using Linux IO Systems locking

### Step 3:

Execute the C Program for the desired output. 

# PROGRAM:

## 1.To Write a C program that illustrates files copying 
```

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }

    int src, dest;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Open source file (read only)
    src = open(argv[1], O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Open destination file (create if not exists)
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(src);
        exit(1);
    }

    // Copy data
    while ((bytes_read = read(src, buffer, BUFFER_SIZE)) > 0) {
        write(dest, buffer, bytes_read);
    }

    printf("File copied successfully.\n");

    close(src);
    close(dest);

    return 0;
}
```






## 2.To Write a C program that illustrates files locking

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


## OUTPUT
![Output](image/copy.png)
![Output](image/lock.png)




# RESULT:
The programs are executed successfully.
