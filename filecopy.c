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
