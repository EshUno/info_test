#include "sharedbuf.h"
#include "thread_1.h"
#include "thread_2.h"
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

/*static void sig_handler(int sig)
{

}*/


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


int main()
{
    SharedBuf shared_buf;
    thread_1 thr1(shared_buf);
    thr1.start();
    thread_2 thr2(shared_buf);
    thr2.start();


     /*   if(signal(SIGINT, sig_handler) == SIG_ERR)
           std::cerr<< "signal processing" << std::endl;
        if(signal(SIGTERM, sig_handler) == SIG_ERR)
           std::cerr<< "signal processing" << std::endl;
    */
    thr1.stop();
    thr2.stop();
    return 0;
}
