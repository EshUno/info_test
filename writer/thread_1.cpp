#include "thread_1.h"
#include <algorithm>
#include <unistd.h>
#include <cstring>
#include <poll.h>

thread_1::thread_1(SharedBuf &buf): shared_buf(buf)
{

}

thread_1::~thread_1()
{

}

void thread_1::start()
{
    thr1 = std::thread(&thread_1::work, this);
}

void thread_1::work()
{
    std::string data;
    while (getline(std::cin, data))
    {
        if (!(data.size() <= 64) || !(all_sym_is_digit(data)))
            std::cout<<"wrong string"<<std::endl;
        else
        {
            std::sort(data.begin(), data.end(),
                      [](auto a, auto b){ return a > b;});
            convert_string(data);
        }
    }
}

void thread_1::convert_string(std::string &data)
{
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

void thread_1::stop()
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
