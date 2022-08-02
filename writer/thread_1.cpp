#include "thread_1.h"
#include <algorithm>

thread_1::thread_1(SharedBuf &buf): shared_buf(buf)
{

}

thread_1::~thread_1()
{
    stop_thr1();
}

void thread_1::start_thr1()
{
    thr1 = std::thread(&thread_1::work, this);
}

void thread_1::work()
{
    std::string data;
    std::cout<< "Press ctrl+с for end" << std::endl;
    while (std::getline(std::cin, data))
    {
        if (!(data.size() <= 64) || !(all_sym_is_digit(data)))
            std::cout<<"Wrong string"<<std::endl;
        else
        {
            std::sort(data.begin(), data.end(),
                      [](auto a, auto b){ return a > b;});
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
        }
    }

}

void thread_1::stop_thr1()
{
    if (thr1.joinable())
        thr1.join();
}

bool thread_1::all_sym_is_digit(std::string &data)
{
    for (auto &symbol: data)
    {
        if (!isdigit(symbol)) return false;
    }
    return true;
}
