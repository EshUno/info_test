#include "thread_2.h"

thread_2::thread_2(SharedBuf &buf): shared_buf(buf)
{

}

thread_2::~thread_2()
{
    stop();
}

void thread_2::start()
{
    thr2 = std::thread(&thread_2::work, this);
}

void thread_2::work()
{
    // TODO: sockets
    /*int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) std::cerr<< "socket failed" << std::endl;

    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_NUM);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    while (true)
    {
        auto sum = shared_buf.wait_and_get_data();
        while(!sum.empty() && !connect(sock, reinterpret_cast<struct sockaddr *>( &addr), sizeof(addr)))
        {
            if (send(sock, reinterpret_cast<void *>(&sum.front()), sizeof(sum.front()), 0))
                sum.pop();
        }
    }

    close(sock);*/
    while(true){
        auto sum = shared_buf.wait_and_get_data();
        if (sum.empty()) return;
        while (!sum.empty())
        {
            std::cout<<sum.front()<<"sum_front"<<std::endl;
            sum.pop();
        }
    }
}

void thread_2::stop()
{
    if (thr2.joinable())
        thr2.join();
}
