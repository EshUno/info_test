#include "sharedbuf.h"

SharedBuf::SharedBuf()
{
    stopped = false;

}

void SharedBuf::stop()
{
    std::unique_lock<std::mutex> lock(mtx);
    stopped = true;
    cv.notify_one();
}

void SharedBuf::put_data(const std::string &str)
{
    std::unique_lock<std::mutex> lock(mtx);
    if (stopped)
        return;
    buff.push(str);
    cv.notify_one();
}

std::queue<std::string> SharedBuf::wait_and_get_data()
{
    std::queue<std::string>  data_buff;
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){return !buff.empty() || stopped;});
        if (stopped)
            return {};
        data_buff = move(buff);
    }
    return data_buff;
}
