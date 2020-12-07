#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
    if(argc<=3)
    {
        printf("usage:%s ip_address port_number filename\n",basename(argv[0]));
        return 1;
    }
    const char* ip=argv[1];
    int port=atoi(argv[2]);
    const char* file_name=argv[3];

    int filefd=open(file_name,O_RDONLY);
    assert(filefd>0);
    struct stat stat_buf;
    fstat(filefd,&stat_buf);

    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    inet_pton(AF_INET,ip,&address.sin_addr);

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);

    int ret=bind(sockfd,(sockaddr*)&address,sizeof(address));
    assert(ret!=-1);

    ret=listen(sockfd,5);
    assert(ret!=-1);

    sockaddr_in client;
    socklen_t len=sizeof(client);
    int connfd=accept(sockfd,(sockaddr*)&client,&len);
    assert(connfd>=0);
    sendfile(connfd,filefd,NULL,stat_buf.st_size);
    close(connfd);
    close(sockfd);
    return 0;
}
