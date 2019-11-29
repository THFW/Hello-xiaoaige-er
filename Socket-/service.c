/*************************************************************************
	> File Name: Server.c
	> Author: zwei
	> E-mail: 740508498@qq.com 
	> Created Time: 2017年12月13日 星期三   15:20
    > Personal Blog: 
 ************************************************************************/

#include<netinet/in.h>  // sockaddr_in
#include<sys/types.h>   // socket
#include<sys/socket.h>  // socket
#include<stdio.h>       // printf
#include<stdlib.h>      // exit
#include<string.h>      // bzero

#define SERVER_PORT 8000
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(void)
{
    // 声明并初始化一个服务器端的socket地址结构
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // 创建socket，若成功，返回socket描述符
    int server_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket_fd < 0)
    {
        perror("Create Socket Failed:");
        exit(1);
    }
    int opt = 1;
    setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
/*
		//开始发送
		timeout.tv_sec = 600;
			timeout.tv_usec = 0;
			//超时机制设置方式接收超时可以随时设置
		setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
*/
    // 绑定socket和socket地址结构
    if(-1 == (bind(server_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))))
    {
        perror("Server Bind Failed:");
        exit(1);
    }
    
    // socket监听
    if(-1 == (listen(server_socket_fd, LENGTH_OF_LISTEN_QUEUE)))
    {
        perror("Server Listen Failed:");
        exit(1);
    }

    while(1)
    {
    		//必须把accept 放到里面
        // 定义客户端的socket地址结构
        struct sockaddr_in client_addr;
        socklen_t client_addr_length = sizeof(client_addr);

        // 接受连接请求，返回一个新的socket(描述符)，这个新socket用于同连接的客户端通信
        // accept函数会把连接到的客户端信息写到client_addr中
        int new_server_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_length);
        if(new_server_socket_fd < 0)
        {
            perror("Server Accept Failed:");
         //   break;
        }

        // recv函数接收数据到缓冲区buffer中
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        if(recv(new_server_socket_fd, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Server Recieve Data Failed:");
            break;
        }

        // 然后从buffer(缓冲区)拷贝到file_name中
        char opreation[FILE_NAME_MAX_SIZE+1];
        bzero(opreation, FILE_NAME_MAX_SIZE+1);
        strncpy(opreation, buffer, strlen(buffer)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(buffer));
        printf("opreation : %s\n", opreation);

		
	if (strcmp("get",opreation)==0)
	{
		// 打开文件并读取文件数据
		FILE *fp = fopen("img.tar", "r");
		if(NULL == fp)
		{
			printf("File:%s Not Found\n", "img.tar");
		}
		else
		{
			bzero(buffer, BUFFER_SIZE);
			int length = 0;
			// 每读取一段数据，便将其发送给客户端，循环直到文件读完为止
			while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
			{
				if(send(new_server_socket_fd, buffer, length, 0) < 0)
				{
				printf("Send File:%s Failed./n", "img.tar");
				break;
				}
				bzero(buffer, BUFFER_SIZE);
			}
			fflush(fp);

			// 关闭文件
			fclose(fp);
			printf("File:%s Transfer Successful!\n", "img.tar");
		}
		// 关闭与客户端的连接
		close(new_server_socket_fd);
	}
	else if (strcmp("put",opreation)==0)
	{
		// 打开文件，准备写入
		FILE *fp = fopen("rootfs", "w");
		if(NULL == fp)
		{
			printf("File:\t%s Can Not Open To Write\n", "rootfs");
			exit(1);
		}

		// 从服务器接收数据到buffer中
		// 每接收一段数据，便将其写入文件中，循环直到文件接收完并写完为止
		bzero(buffer, BUFFER_SIZE);
		int length = 0;
		while((length = recv(new_server_socket_fd, buffer, BUFFER_SIZE, 0)) > 0)
		{
			if(fwrite(buffer, sizeof(char), length, fp) < length)
			{
				printf("File:\t%s Write Failed\n", "rootfs");
				break;
			}
			bzero(buffer, BUFFER_SIZE);
		}
		fflush(fp);
		close(fp);
	}
    }
    // 关闭监听用的socket
    close(server_socket_fd);
    return 0;
}
