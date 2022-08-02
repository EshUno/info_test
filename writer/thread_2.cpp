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
