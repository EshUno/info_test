#include "thread_2.h"
#include "addr.h"
#include <sys/socket.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

thread_2::thread_2(SharedBuf &buf): shared_buf(buf)
{

}

thread_2::~thread_2()
{
    stop();
}

void thread_2::start()
{
    errno = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        throw std::runtime_error(std::string("thread_2: ") + strerror(errno));
    }
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_NUM);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    thr2 = std::thread(&thread_2::work, this);
}

void thread_2::work()
{   

    connect(sock, reinterpret_cast<struct sockaddr *>( &addr), sizeof(addr));
    while(true){
        //возвращает пустую строку если прервался поток 1
        auto sum = shared_buf.wait_and_get_data();
        if (sum.empty()) stop();
        while (!sum.empty())
        {
            send(sock, reinterpret_cast<void *>(&sum.front()), sizeof(sum.front()), 0);
            sum.pop();
            std::cout<<sum.front()<<"sum_front"<<std::endl;
        }
    }

}

void thread_2::stop()
{
    close(sock);
    if (thr2.joinable())
        thr2.join();
}
