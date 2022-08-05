#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include "addr.h"
#include <unistd.h>
#include <arpa/inet.h>

bool num_is_good(int num)
{
    return ((num > 99) && (num % 32 == 0));
}

int main(int argc, char *argv[])
{
    errno = 0;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        std::cout<< "socket failed"<< strerror(errno) << std::endl;
        return 1;
    }
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(struct sockaddr_in));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT_NUM);
    if (argc == 2)
    {
        s_addr.sin_port = htons(std::atoi(argv[1]));
    }
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if( setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)
    {
        std::cout<<"sectopt failed" << strerror(errno) <<std::endl;
        return 1;
    }

    if (bind(server_fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0)
    {
        std::cout<<"bind failed" << strerror(errno) <<std::endl;
        return 1;
    }
    if (listen(server_fd, SOMAXCONN) < 0)
    {
        std::cout<<"listen failed" << strerror(errno) <<std::endl;
        return 1;
    }
    int client_fd, sum;
    for(;;)
    {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0)
        {
            std::cout<< "accept failed"<< strerror(errno) << std::endl;
            return 1;
        }
        while(true)
        {
            int res = recv(client_fd, &sum, sizeof(sum), 0);
            if (res < 0)
            {
                std::cout<< "recv failed"<< strerror(errno) << std::endl;
                return 1;
            }

            if (res == 0)
            {
                std::cout << "writer has disconnected" << std::endl;
                break;
            }

            auto no = ntohl(sum);
            if (num_is_good(no))
                std::cout<< "got result: "<< no << std::endl;
            else
                std::cout<< "error result "<< no << std::endl;
        }
    }
    close(client_fd);
    close(server_fd);
    return 0;
}
