#include <iostream>
#include <string>
#include <unistd.h> 
#include <sys/wait.h>
#include <cstring>
#include "parent.h"

void ParentRoutine(std::string& fileName) {
    std::string output_file = fileName;
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Ошибка при создании pipe");
        return;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("Ошибка при fork()");
        return;
    }

    if (pid == 0) {
        close(fd[1]); 

       
        char pipe_read_fd[10], file_name_arg[256];
        sprintf(pipe_read_fd, "%d", fd[0]);
        strcpy(file_name_arg, output_file.c_str());

        const char *exe = "./child";

        char *args[] = {(char *)exe, pipe_read_fd, file_name_arg, NULL};

        execve("./child", args, NULL);
        perror("execve");
        exit(1);
    } else {
        close(fd[0]);

        std::string input_data;
        std::cout << "Введите числа через пробел: ";
        std::getline(std::cin, input_data);

        write(fd[1], input_data.c_str(), input_data.size());
        close(fd[1]);

        wait(NULL);
    }
}

int main() {

    std::string output_file;
    std::cout << "Введите название файла для вывода результата: ";
    std::getline(std::cin, output_file);
    ParentRoutine(output_file);
    return 0;
}
