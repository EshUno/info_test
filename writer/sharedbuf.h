#ifndef SHAREDBUF_H
#define SHAREDBUF_H

#include <condition_variable>
#include <mutex>
#include <string>
#include <iostream>
#include <queue>

class SharedBuf final
{
public:
    SharedBuf();
    void put_data(const std::string &str);
    std::queue<int> wait_and_get_data();

private:
    std::queue<std::string> buff;
    bool data_ready;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif // SHAREDBUF_H
