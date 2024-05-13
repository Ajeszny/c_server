#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char* load_file_from_disk(const char* filename) {
    FILE* fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* result = malloc((size*sizeof(char))+1);
    for (int i = 0; i < size; ++i) {
        fscanf(fp, "%c", result+i);
    }
    result[size] = 0;
    fclose(fp);
    return result;
};

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(int));
    int μαλακασ;
    struct sockaddr_in cock;
    μαλακασ = sizeof(cock);
    cock.sin_addr.s_addr = INADDR_ANY;
    cock.sin_port = htons(80);
    cock.sin_family = AF_INET;
    int err = bind(fd, &cock, sizeof(cock));
    if (err == -1) {
        perror("Shit");
        return 69;
    }

    listen(fd, 3);
    while(1) {
        char* response = load_file_from_disk("index.html");
        int len = strlen(response);
        int acceptor_fd = accept(fd, &cock, &μαλακασ);
        send(acceptor_fd, response, len + 1, 0);
        close(acceptor_fd);
        free(response);
    }

    close(fd);
    return 0;
}
