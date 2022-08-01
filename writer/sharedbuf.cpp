#include "sharedbuf.h"

SharedBuf::SharedBuf()
{
    data_ready = false;

}

void SharedBuf::put_data(const std::string &str)
{
    std::unique_lock<std::mutex> lock(mtx);
    buff.push(str);
    data_ready  = true;
    cv.notify_one();
}

std::queue<int> SharedBuf::wait_and_get_data()
{
    std::queue<std::string>  data_buff;
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){return data_ready;});
        data_buff = move(buff);
        data_ready  = false;
    }
    std::queue<int> sum_buff;
    while (!data_buff.empty())
    {
        std::cout << "Thr2: got string " << data_buff.front() << std::endl;
        int sum = 0;
        for (auto &symbol:data_buff.front())
        {
            if (isdigit(symbol)){
                sum += symbol;
            }
        }
        sum_buff.push(sum);
    }
    return sum_buff;
}
