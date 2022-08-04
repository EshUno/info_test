#include "thread_2.h"
#include "addr.h"
#include <sys/socket.h>
#include <chrono>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>


thread_2::thread_2(SharedBuf &buf): shared_buf(buf)
{
    stopped = false;
}

thread_2::~thread_2()
{

}

void thread_2::start()
{
    create_socket();
    thr2 = std::thread(&thread_2::work, this);
}

void thread_2::create_socket()
{
    errno = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        throw std::runtime_error(std::string("thread_2: ") + strerror(errno));
    }
    addr_fill();
}

void thread_2::addr_fill()
{
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT_NUM);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

void thread_2::work()
{   
    thr3 = std::thread(&thread_2::thr_connect, this);
    while(true){
         //возвращает пустую очередь если прервался поток 1
        auto sum_buff = shared_buf.wait_and_get_data();
        if (sum_buff.empty())
        {
            break;
        }
        while (!sum_buff.empty())
        {
            push_sum(count_sum(sum_buff.front()));
            sum_buff.pop();
        }
    }
    thr_connect_stop();
}

int thread_2::count_sum(std::string &buff_elem)
{
    std::cout << "thr2: got string: " << buff_elem << std::endl;
    int sum = 0;
    for (auto &symbol:buff_elem)
    {
        if (isdigit(symbol)){
            sum += symbol - '0';
        }
    }
    return sum;
}

void thread_2::push_sum(int sum)
{
    std::unique_lock<std::mutex> lock(mtx);
    shared_sum.push(sum);
    cv.notify_one();
}

void thread_2::thr_connect_stop()
{
    std::unique_lock<std::mutex> lock(mtx);
    stopped = true;
    cv.notify_one();
}

void thread_2::thr_connect()
{
    int sum = -1;
    bool connected = false;

    while(true)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this](){return !shared_sum.empty() || stopped;});
            if (stopped) return;
            sum = shared_sum.front();
            shared_sum.pop();

        }

        while (sum != -1)
        {
            errno = 0;
            if (!connected)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                auto connectRes = connect(sock, reinterpret_cast<struct sockaddr *>( &addr), sizeof(addr));
                if (connectRes == 0)
                {
                    connected = true;
                }
                else
                {
                    std::cout << "connect: " << strerror(errno) << std::endl;
                    if (stopped) return;
                }
            }

            if(connected)
            {
                std::cout<< sum << std::endl;
                auto no = htonl(sum);
                errno = 0;
                int sendRes = send(sock, reinterpret_cast<void *>(&no), sizeof(sum), MSG_NOSIGNAL);
                if (sendRes < 0)
                {
                    if (errno == EPIPE)
                    {
                        close(sock);
                        create_socket();
                        connected = false;
                    }
                    std::cout << "send: error " << strerror(errno) << std::endl;
                }
                else
                {
                    sum = -1;
                }
            }
        }
    }
}

void thread_2::stop()
{
    close(sock);
    if (thr2.joinable())
        thr2.join();
    if (thr3.joinable())
        thr3.join();
}
