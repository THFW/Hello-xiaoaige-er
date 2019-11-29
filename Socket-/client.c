/*************************************************************************
	> File Name: Client.c
	> Author: zwei
	> E-mail: 740508498@qq.com 
	> Created Time: 2017��12��13�� ������   15:51
    > Personal Blog: 
 ************************************************************************/
//ʵ�ֹ��ܷ�������ͻ��˻��ഫ�ļ�
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
	// ��������ʼ��һ���ͻ��˵�socket��ַ�ṹ
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);
	char *error;

	// ����socket�����ɹ�������socket������
	int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket_fd < 0)
	{
		perror("Create Socket Failed:");
		exit(1);
	}

	// �󶨿ͻ��˵�socket�Ϳͻ��˵�socket��ַ�ṹ �Ǳ���
	if(-1 == (bind(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr))))
	{
		perror("Client Bind Failed:");
		exit(1);
	}

	// ����һ���������˵�socket��ַ�ṹ��
	//���÷������Ǳߵ�IP��ַ���˿ڶ�����г�ʼ�������ں��������
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

	// ��������������ӣ�
	//���ӳɹ���client_socket_fd
	//�����˿ͻ��˺ͷ�������һ��socket����
	if(connect(client_socket_fd, (struct sockaddr*)&server_addr, server_addr_length) < 0)
	{
	perror("Can Not Connect To Server IP:");
	exit(0);
	}

	// �����ļ��� ���ŵ�������buffer�еȴ�����
	char opretion[FILE_NAME_MAX_SIZE+1];
	bzero(opretion, FILE_NAME_MAX_SIZE+1);
	printf("Please Input operation:\t");
	scanf("%s", opretion);

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);
	strncpy(buffer, opretion, strlen(opretion)>BUFFER_SIZE?BUFFER_SIZE:strlen(opretion));

	// �����������buffer�е�����
	if(send(client_socket_fd, buffer, BUFFER_SIZE, 0) < 0)
	{
		perror("Send File Name Failed:");
		exit(1);
	}

	if (strcmp("get",opretion)==0)
	{
		// ���ļ���׼��д��
		FILE *fp = fopen("img.tar", "w");
		if(NULL == fp)
		{
			printf("File:\t%s Can Not Open To Write\n", "img.tar");
			exit(1);
		}

		// �ӷ������������ݵ�buffer��
		// ÿ����һ�����ݣ��㽫��д���ļ��У�ѭ��ֱ���ļ������겢д��Ϊֹ
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
			// ÿ��ȡһ�����ݣ��㽫�䷢�͸���������ѭ��ֱ���ļ�����Ϊֹ
			while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp)) > 0)
			{
				if(send(client_socket_fd, buffer, length, 0) < 0)
				{
					printf("Send File:%s Failed./n", "rootfs");
					break;
				}
				bzero(buffer, BUFFER_SIZE);
			}

		// �ر��ļ�
		fflush(fp);
		fclose(fp);
		printf("File:%s Transfer Successful!\n","rootfs");
		}

	}
	// ���ճɹ��󣬹ر��ļ����ر�socket
	printf("Receive File:\t%s From Server IP Successful!\n", "rootfs");
	error =( char * )malloc(4*sizeof(int));
	close(client_socket_fd);
	return 0;
}
