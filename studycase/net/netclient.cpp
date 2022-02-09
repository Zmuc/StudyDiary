#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/socket.h>

#define SERVICE_PORT 7000
#define BUFFER_SIZE 1024

int main() {
	// 创建sockfd
	int sock_client = socket(AF_INET, SOCK_STREAM, 0);

	// 定义服务器端网络通信地址结构体
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVICE_PORT);            // 服务器端口
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 服务器ip

	/*
	函数：int connect(SOCKET s, const struct sockaddr * addr, int addrlen); 客户端来建立与服务器端的连接
	s：标识一个未connect套接口的描述字；
	addr：指向要连接套接字的sockaddr类结构体类型的指针；
	addrlen：addr结构体的字节长度。
	*/
	// 连接服务器，失败返回1
	if (connect(sock_client, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("connect");
		exit(1);
	}

	// 通信
	char send_buf[BUFFER_SIZE];
	char recv_buf[BUFFER_SIZE];
	while(fgets(send_buf, sizeof(send_buf), stdin) != NULL) {
		// 发送，将标准输入发送到服务器端
		send(sock_client, send_buf, strlen(send_buf), 0);
		if (strcmp(send_buf, "exit\n") == 0) {
			break;
		}

		// 接收，接收服务器端的返回信息到标准输出
		recv(sock_client, recv_buf, sizeof(recv_buf), 0);
		printf("SERVICE: %s\n", recv_buf);

		// 重置刷新
		memset(send_buf, 0, sizeof(send_buf));
		memset(recv_buf, 0, sizeof(recv_buf));
	}

	// 关闭sockfd
	close(sock_client);
	return 0;
}
