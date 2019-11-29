/*************************************************************************
	> File Name: Server.c
	> Author: zwei
	> E-mail: 740508498@qq.com 
	> Created Time: 2017��12��13�� ������   15:20
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
    // ��������ʼ��һ���������˵�socket��ַ�ṹ
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // ����socket�����ɹ�������socket������
    int server_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket_fd < 0)
    {
        perror("Create Socket Failed:");
        exit(1);
    }
    int opt = 1;
    setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
/*
		//��ʼ����
		timeout.tv_sec = 600;
			timeout.tv_usec = 0;
			//��ʱ�������÷�ʽ���ճ�ʱ������ʱ����
		setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(struct timeval));
*/
    // ��socket��socket��ַ�ṹ
    if(-1 == (bind(server_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))))
    {
        perror("Server Bind Failed:");
        exit(1);
    }
    
    // socket����
    if(-1 == (listen(server_socket_fd, LENGTH_OF_LISTEN_QUEUE)))
    {
        perror("Server Listen Failed:");
        exit(1);
    }

    while(1)
    {
    		//�����accept �ŵ�����
        // ����ͻ��˵�socket��ַ�ṹ
        struct sockaddr_in client_addr;
        socklen_t client_addr_length = sizeof(client_addr);

        // �����������󣬷���һ���µ�socket(������)�������socket����ͬ���ӵĿͻ���ͨ��
        // accept����������ӵ��Ŀͻ�����Ϣд��client_addr��
        int new_server_socket_fd = accept(server_socket_fd, (struct sockaddr*)&client_addr, &client_addr_length);
        if(new_server_socket_fd < 0)
        {
            perror("Server Accept Failed:");
         //   break;
        }

        // recv�����������ݵ�������buffer��
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        if(recv(new_server_socket_fd, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Server Recieve Data Failed:");
            break;
        }

        // Ȼ���buffer(������)������file_name��
        char opreation[FILE_NAME_MAX_SIZE+1];
        bzero(opreation, FILE_NAME_MAX_SIZE+1);
        strncpy(opreation, buffer, strlen(buffer)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(buffer));
        printf("opreation : %s\n", opreation);

		
	if (strcmp("get",opreation)==0)
	{
		// ���ļ�����ȡ�ļ�����
		FILE *fp = fopen("img.tar", "r");
		if(NULL == fp)
		{
			printf("File:%s Not Found\n", "img.tar");
		}
		else
		{
			bzero(buffer, BUFFER_SIZE);
			int length = 0;
			// ÿ��ȡһ�����ݣ��㽫�䷢�͸��ͻ��ˣ�ѭ��ֱ���ļ�����Ϊֹ
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

			// �ر��ļ�
			fclose(fp);
			printf("File:%s Transfer Successful!\n", "img.tar");
		}
		// �ر���ͻ��˵�����
		close(new_server_socket_fd);
	}
	else if (strcmp("put",opreation)==0)
	{
		// ���ļ���׼��д��
		FILE *fp = fopen("rootfs", "w");
		if(NULL == fp)
		{
			printf("File:\t%s Can Not Open To Write\n", "rootfs");
			exit(1);
		}

		// �ӷ������������ݵ�buffer��
		// ÿ����һ�����ݣ��㽫��д���ļ��У�ѭ��ֱ���ļ������겢д��Ϊֹ
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
    // �رռ����õ�socket
    close(server_socket_fd);
    return 0;
}
