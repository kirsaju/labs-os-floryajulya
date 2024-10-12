#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <pipe_read_fd> <output_file>\n", argv[0]);
        return 1;
    }


    int pipe_read_fd = atoi(argv[1]);

    int file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("open");
        return 1;
    }

    char buffer[256];
    read(pipe_read_fd, buffer, sizeof(buffer));
    close(pipe_read_fd);

    float sum = 0;
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        sum += atof(token);
        token = strtok(NULL, " ");
    }

    dprintf(file, "%f", sum);
    close(file);

    return 0;
}
