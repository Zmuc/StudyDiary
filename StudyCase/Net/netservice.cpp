#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;

#define PORT 7000
#define QUEUE 20
int conn;

int main() {
	/*
	函数：int socket(int af, int type, int protocol)； 创建套接字
	af：协议簇/地址簇，仅支持AF_INET格式，即ARPA Internet地址格式，默认IPV4；
	type：类型，如TCP（SOCK_STREAM）和UDP（SOCK_DGRAM），默认为TCP;
	protocol：协议，如IPPROTO_TCP、IPPROTO_UDP、IPPROTO_STCP、IPPROTO_TIPC等，0则自动选择合适协议。
	*/
	// 创建sockfd
	int sock_service = socket(AF_INET, SOCK_STREAM, 0);

	/* 
	sockaddr_in：用来处理网络通信的地址
	struct sockaddr_in {
		unsigned short int sin_family;   // sa_family_t，地址簇
		unsigned short int sin_port;     // in_port_t，uint16_t，16位TCP/UDP端口号
		struct in_addr sin_addr;         // 32位IP地址
		char sin_zero[8];                // 不使用
	}

	struct in_addr { 
    	unsigned int s_addr;            // uint32_t，in_addr_t，32位IP地址
    }
	*/
	// 定义服务器端网络通信地址结构体
	struct sockaddr_in server_sockaddr;
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(PORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*
	函数：int bind(int sockfd , const struct sockaddr * addr, socklen_t addrlen); 把一个本地协议地址赋予一个套接字
	addr：指向sockaddr类（sockaddr_in/sockaddr_in6等）结构体类型的指针；
	addrlen：addr结构体的长度，可以用sizeof操作符获得。
	*/
	// 绑定
	if (bind(sock_service, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr)) == -1) {
		perror("bind");
		exit(1);
	}

	/*
	函数：int listen(int sockfd, int backlog); 监听一个套接字
	sockfd：标识一个已bind未connect套接口的描述字；
	backlog：等待连接队列的最大长度；
	*/
	// 监听
	if (listen(sock_service, QUEUE) == -1) {
		perror("listen");
		exit(1);
	}

	// 定义客户端网络通信地址结构体
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
    
	/*
	函数：SOCKET accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); 接收客户端connect请求
	sockfd：标识一个已listen套接口的描述字；
	addr：指向一个缓冲区，其中接收为通讯层所知的连接实体（客户端）的地址； // 可选
	addrlen：输入参数，配合addr一起使用，指向存有addr地址长度的整型数。  // 可选
	*/
	// 接收， 成功返回非负描述字，出错返回-1
	conn = accept(sock_service, (struct sockaddr *) &client_addr, &length);    
	if (conn < 0) {
		perror("connect");
		exit(1);
	}

	// 通信
	char buffer[1024];
	while (1) {
		// 重置刷新
        memset(buffer, 0, sizeof(buffer));
        
		/*
		函数：int recv(SOCKET s, char *buf, int len, int flags); 网络I/O操作，接收
		s：标识一个已accept套接口的描述字，接收端；
		buf：指向一个缓冲区，该缓冲区用来存放recv函数接收到的数据；
		len：buf的长度；
		flags：一般置0。
		*/
        // 读取，接收客户端发送的信息
        int len = recv(conn, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "exit\n") == 0 || strcmp(buffer, "") == 0) {
			break;
		}
        printf("SERVICE: %s", buffer);

		/*
		函数：int send(SOCKET s, const char *buf, int len, int flags); 网络I/O操作，发送
		s：标识一个已accept套接口的描述字，发送端；
		buf：指向一个缓冲区，该缓冲区用来存放send函数要发送的数据；
		len：实际要发送的数据的字节数；
		flags：一般置0。
		*/
        // 发送，完整的请求必须要有返回数据
        send(conn, buffer, len, 0);
    }

	/*
	函数：close(sockfd); 关闭套接字
	*/
	// 关闭套接字
    close(conn);
    close(sock_service);
    return 0;
}
