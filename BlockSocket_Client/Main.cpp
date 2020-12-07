#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <time.h>
#include <chrono>
#include <thread>

int main()
{
    int SERVER_PORT = 1234;
    const char * SERVER_ADDR = "127.0.0.1";

    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serverAddr.sin_port = htons(SERVER_PORT);

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    int ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        printf("连接失败\n");
        close(clientSocket);
        return -1;
    }

    while(1){
        int dataLen = 32;
        unsigned char data[] = {
                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                'A', 'B', 'C', 'D', 'E', 'F'
        };

        int sendedDataLen = 0;
        while(sendedDataLen < dataLen){
            int ret = send(clientSocket, data + sendedDataLen, dataLen - sendedDataLen, 0);
            printf("ret: %d\n", ret);
            sendedDataLen += ret;
        }

        int recvedDataLen = 0;
        while(recvedDataLen < dataLen){
            int ret = recv(clientSocket, data + recvedDataLen, dataLen - recvedDataLen, 0);
            printf("ret: %d\n", ret);
            recvedDataLen += ret;
        }

        for(int i=0;i<dataLen;i++){
            printf("%c", data[i]);
        }
        printf("\n");

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}