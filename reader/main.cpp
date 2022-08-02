#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include "addr.h"
#include <unistd.h>

bool num_is_good(int num)
{
    return ((num / 100) && !(num % 32));
}

int main()
{
   /* int sock_listen = socket(AF_UNIX, SOCK_STREAM, 0), len = 0;
    int sum;
    struct sockaddr sa;
    sa.sa_family = AF_UNIX;
    strcpy(sa.sa_data, SOCKADDR_UNIX);
    len = sizeof(sa.sa_family) + strlen(sa.sa_data);
    errno = 0;
    unlink(SOCKADDR_UNIX);
    if (bind(sock_listen, &sa, len) < 0)
    {
        std::cout<<"Bind failed" << strerror(errno) <<std::endl;
        return 0;
    }
    if (listen(sock_listen, SOMAXCONN) < 0)
    {
        std::cout<<"Listen failed" << strerror(errno) <<std::endl;
        return 0;
    }
    int sock = accept(sock_listen, NULL, NULL);
    if (sock < 0)
    {
         std::cout<<"Accept failed" << strerror(errno) <<std::endl;
         return 0;
    }
    int maxLength = sizeof(sum);
    errno = 0;
    int rc = setsockopt(sock, SOL_SOCKET, SO_RCVLOWAT, &maxLength, sizeof(maxLength));
    if (rc < 0)
    {
         std::cout << "Setsockopt failed: " << strerror(errno) << std::endl;
    }
    while(true)
    {
        if (recv(sock, &sum, sizeof(int), 0) < 0)
            break;
        if (num_is_good(sum))
        {
            std::cout<<"Data has been received "<<sum<<std::endl;
        }
        else
        {
            std::cout<<"Error"<<std::endl;
        }
    }
    unlink(SOCKADDR_UNIX);
    close(sock_listen);
    close(sock);*/
    return 0;
}
