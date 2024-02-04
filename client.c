#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1340);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int err = connect(fd, &addr, sizeof(addr));
    if (err == -1) {
        perror("Server is not running");
        return 1;
    }
    char to_send[] = "Siemanko Duch", hello[1337];
    send(fd, to_send, strlen(to_send) + 1, 0);
    read(fd, hello, 1337);
    printf("%s", hello);
    uint8_t fuck_off;
    read(fd, &fuck_off, 1);
    close(fd);
}
