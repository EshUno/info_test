#include "sharedbuf.h"

SharedBuf::SharedBuf()
{
    data_ready = false;

}

void SharedBuf::put_data(const std::string &str)
{
    std::unique_lock<std::mutex> lock(mtx);
    buf = str;
    data_ready  = true;
    cv.notify_one();
}

int SharedBuf::wait_and_get_data()
{
    std::string data;
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){return data_ready;});
        data = buf;
        data_ready  = false;
    }
    std::cout << "Thr2: got string " << data << std::endl;
    int sum = 0;
    for (auto &symbol:data)
    {
        if (isdigit(symbol)){
            sum += symbol;
        }
    }
    return sum;
}
