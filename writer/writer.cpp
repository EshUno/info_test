#include "sharedbuf.h"
#include "thread_1.h"
#include "thread_2.h"
#include "addr.h"
#include <algorithm>
#include <thread>
#include <signal.h>

#include <cstring>
int main()
{
    try{
        sigset_t block_mask;
        sigemptyset(&block_mask);
        sigaddset(&block_mask, SIGINT);
        sigaddset(&block_mask, SIGTERM);
        sigaddset(&block_mask, SIGQUIT);

        if (pthread_sigmask(SIG_SETMASK, &block_mask, nullptr) != 0)
        {
            std::cerr << "pthread_sigmask" << std::endl;
            return 1;
        }
        else
        {
            SharedBuf shared_buf;
            thread_1 thr1(shared_buf);
            thr1.start();
            thread_2 thr2(shared_buf);
            thr2.start();
            int sig;
            if(sigwait(&block_mask, &sig) != 0)
            {
                std::cerr << "sigwait" << std::endl;
                return 1;
            }
            thr1.stop();
            shared_buf.stop();
            thr2.stop();
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout<< e.what () << std::endl;
    }
    return 0;
}
