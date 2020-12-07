#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(server_sock < 0) {
        printf("socket() error");
        return -1;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(1234);
    local.sin_addr.s_addr = inet_addr("0.0.0.0");
    socklen_t len = sizeof(local);
    if(bind(server_sock, (struct sockaddr*)&local ,len) < 0) {
        printf("bind() error");
        return -1;
    }

    if(listen(server_sock, 5) < 0) {
        printf("listen() error");
        return -1;
    }

    struct sockaddr_in remote;
    socklen_t socketLen = sizeof(struct sockaddr_in);

    while(1)
    {
        int sock = accept(server_sock, (struct sockaddr*)&remote, &socketLen);
        while(1){
            int dataLen = 32;
            unsigned char data[dataLen];

            int recvedDataLen = 0;
            while(recvedDataLen < dataLen){
                int ret = recv(sock, data + recvedDataLen, dataLen - recvedDataLen, 0);
                recvedDataLen += ret;
            }

            int sendedDataLen = 0;
            while(sendedDataLen < dataLen){
                int ret = send(sock, data + sendedDataLen, dataLen - sendedDataLen, 0);
                sendedDataLen += ret;
            }
        }
    }

    close(server_sock);

    return 0;
}