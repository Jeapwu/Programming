#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

int main(int argc,char* argv[]){
    if(argc<=3){
        printf("ip_address port_number file_path\n");
        return -1;
    }
    const char* ip=argv[1];
    int port=atoi(argv[2]);
    const char* file_path=argv[3];
    //获取文件属性
    int filefd=open(file_path,O_RDONLY);
    assert(filefd>0);
    struct stat stat_buf;
    fstat(filefd,&stat_buf);
    //创建服务端通信套接字
    int sock=socket(AF_INET,SOCK_STREAM,0);
    assert(sock>=0);
    //绑定服务端地址与ip
    struct sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    inet_pton(AF_INET,ip,&address.sin_addr);
    int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
    assert(ret!=-1);
    //监听客户端连接
    ret=listen(sock,5);
    assert(ret!=-1);
    //接受连接
    struct sockaddr_in client;
    socklen_t len=sizeof(client);
    int connfd=accept(sock,(struct sockaddr*)&client,&len);
    //进行通信
    if(connfd<0){
        printf("error is: %d\n",errno);
    }else{
        //发送文件
        sendfile(connfd,filefd,NULL,stat_buf.st_size);
        close(connfd);
    }
    close(sock);
    return 0;
}