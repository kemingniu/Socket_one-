#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>


int main(int argc,char* argv[])
{

    if(argc != 3)
    {
        printf("Usage: ./client [ip] [port]\n");
        return 1;
    }

    int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0)
        {
            perror("socket");
            return 1;
        }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(fd,(struct sockaddr*)&server,sizeof(server));
    
      if(ret < 0)
       {
      perror("connect");
       return 1;
      }else
      {
      printf("connect success!\n");
      }


    while(1)
    {
    char buf[1024] = {0};
    printf(">>>");
    fflush(stdout);
    int read_size = read(0,buf,sizeof(buf)-1);
    if(read_size < 0)
    {
        perror("read");
        continue;
    }
    if(read_size == 0)
    {
        printf("goodbye\n");
        break;
    }
    buf[read_size] = '\0';
    write(fd,buf,strlen(buf));
    char buf_output[1024] = {0};
    ssize_t size = read(fd,buf_output,sizeof(buf_output)-1);
    if(size < 0)
    {
        perror("read");
        continue;
    }
    if(size ==0)
    {
        printf("goodbye!");
        break;
    }
    buf_output[size] = '\0';
    printf("%s\n",buf_output);
    }

    close(fd);

    return 0;
}
