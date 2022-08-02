#include "sharedbuf.h"
#include "addr.h"
#include <algorithm>
#include <thread>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>


bool all_sym_id_digit(std::string &data)
{
    for (auto &symbol: data)
    {
        if (!isdigit(symbol)) return false;
    }
    return true;
}

/*static void sig_handler(int sig)
{

}*/

void thread_1(SharedBuf &shared_buf)
{
    std::string data;
    const std::string KB = "KB";
    std::cout<< "Press ctrl+с for end" << std::endl;
    while (std::getline(std::cin, data))
    {
        if ((data.size() <= 64) && (all_sym_id_digit(data)))
        {
            std::cout<<data<<std::endl;
            std::sort(data.begin(), data.end(), [](auto a, auto b){ return a > b;});
            std::cout<<data<<std::endl;
            std::string ans;
            for(auto &symbol: data)
            {
                int dig = symbol - '0';
                if (dig % 2)
                {
                    ans += symbol;
                }
                else
                {
                    ans += KB;
                }
            }
            shared_buf.put_data(ans);
            std::cout<<ans<<std::endl;
        }
        else std::cout<<"Wrong string"<<std::endl;
    }
    shared_buf.stop();
    return;
}

void thread_2(SharedBuf &shared_buf)
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
    auto sum = shared_buf.wait_and_get_data();
    while (!sum.empty())
    {
        std::cout<<sum.front()<<std::endl;
        sum.pop();
    }
}

int main()
{
    SharedBuf shared_buf;
    try
    {
        auto thr1 = std::thread(thread_1, std::ref(shared_buf));
        auto thr2 = std::thread(thread_2, std::ref(shared_buf));

     /*   if(signal(SIGINT, sig_handler) == SIG_ERR)
           std::cerr<< "signal processing" << std::endl;
        if(signal(SIGTERM, sig_handler) == SIG_ERR)
           std::cerr<< "signal processing" << std::endl;
    */
        thr1.join();
        thr2.join();
    }  catch (const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
