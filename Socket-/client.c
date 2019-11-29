/*************************************************************************
	> File Name: Client.c
	> Author: zwei
	> E-mail: 740508498@qq.com 
	> Created Time: 2017年12月13日 星期三   15:51
    > Personal Blog: 
 ************************************************************************/
//实现功能服务器与客户端互相传文件
#include<netinet/in.h>   // sockaddr_in
#include<sys/types.h>    // socket
#include<sys/socket.h>   // socket
#include<stdio.h>        // printf
#include<stdlib.h>       // exit
#include<string.h>       // bzero

#define SERVER_PORT 8000
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main()
{
	// 声明并初始化一个客户端的socket地址结构
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);
	char *error;

	// 创建socket，若成功，返回socket描述符
	int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket_fd < 0)
	{
		perror("Create Socket Failed:");
		exit(1);
	}

	// 绑定客户端的socket和客户端的socket地址结构 非必需
	if(-1 == (bind(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr))))
	{
		perror("Client Bind Failed:");
		exit(1);
	}

	// 声明一个服务器端的socket地址结构，
	//并用服务器那边的IP地址及端口对其进行初始化，用于后面的连接
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == 0)
	{
	perror("Server IP Address Error:");
	exit(1);
	}
	server_addr.sin_port = htons(SERVER_PORT);
	socklen_t server_addr_length = sizeof(server_addr);

	// 向服务器发起连接，
	//连接成功后client_socket_fd
	//代表了客户端和服务器的一个socket连接
	if(connect(client_socket_fd, (struct sockaddr*)&server_addr, server_addr_length) < 0)
	{
	perror("Can Not Connect To Server IP:");
	exit(0);
	}

	// 输入文件名 并放到缓冲区buffer中等待发送
	char opretion[FILE_NAME_MAX_SIZE+1];
	bzero(opretion, FILE_NAME_MAX_SIZE+1);
	printf("Please Input operation:\t");
	scanf("%s", opretion);

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	strncpy(buffer, opretion, strlen(opretion)>BUFFER_SIZE?BUFFER_SIZE:strlen(opretion));

	// 向服务器发送buffer中的数据
	if(send(client_socket_fd, buffer, BUFFER_SIZE, 0) < 0)
	{
		perror("Send File Name Failed:");
		exit(1);
	}

	if (strcmp("get",opretion)==0)
	{
		// 打开文件，准备写入
		FILE *fp = fopen("img.tar", "w");
		if(NULL == fp)
		{
			printf("File:\t%s Can Not Open To Write\n", "img.tar");
			exit(1);
		}

		// 从服务器接收数据到buffer中
		// 每接收一段数据，便将其写入文件中，循环直到文件接收完并写完为止
		bzero(buffer, BUFFER_SIZE);
		int length = 0;
		while((length = recv(client_socket_fd, buffer, BUFFER_SIZE, 0)) > 0)
		{
			if(fwrite(buffer, sizeof(char), length, fp) < length)
			{
				printf("File:\t%s Write Failed\n", "img.tar");
				break;
			}
			bzero(buffer, BUFFER_SIZE);
		}
		fflush(fp);
		close(fp);
	}
	else if (strcmp("put",opretion)==0)
	{     
		FILE *fp = fopen("rootfs", "r");
		if(NULL == fp)
		{
			printf("File:%s Not Found\n", "rootfs");
		}
		else
		{
			bzero(buffer, BUFFER_SIZE);
			int length = 0;
			// 每读取一段数据，便将其发送给服务器，循环直到文件读完为止
			while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
			{
				if(send(client_socket_fd, buffer, length, 0) < 0)
				{
					printf("Send File:%s Failed./n", "rootfs");
					break;
				}
				bzero(buffer, BUFFER_SIZE);
			}

		// 关闭文件
		fflush(fp);
		fclose(fp);
		printf("File:%s Transfer Successful!\n","rootfs");
		}

	}
	// 接收成功后，关闭文件，关闭socket
	printf("Receive File:\t%s From Server IP Successful!\n", "rootfs");
	error =( char * )malloc(4*sizeof(int));
	close(client_socket_fd);
	return 0;
}
