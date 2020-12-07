#include <stdio.h>
#include <netdb.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	assert(argc==2);
	const char* host=argv[1];
	// 获取目标主机地址信息
	hostent* hostinfo=gethostbyname(host);
	assert(hostinfo);
	// 获取daytime服务信息
	servent* servinfo=getservbyname("daytime","tcp");
	assert(servinfo);
	printf("daytime port is %d\n",ntohs(servinfo->s_port));
	// 建立与主机通信socket
	sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=servinfo->s_port;
	address.sin_addr=*(in_addr*)*hostinfo->h_addr_list;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	int result=connect(sockfd,(sockaddr*)&address,sizeof(address));
	assert(result!=-1);
	char buf[128];
	// 读取daytime发送的数据
	result=read(sockfd,buf,sizeof(buf));
	buf[result]='\0';
	// 打印服务器发送来的时间
	printf("the day time is: %s",buf);
	close(sockfd);
	return 0;
}