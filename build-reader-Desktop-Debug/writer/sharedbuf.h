#ifndef SHAREDBUF_H
#define SHAREDBUF_H

#include <condition_variable>
#include <mutex>
#include <string>
#include <iostream>

class SharedBuf final
{
public:
    SharedBuf();
    void put_data(const std::string &str);
    int wait_and_get_data();

private:
    std::string buf;
    bool data_ready;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif // SHAREDBUF_H
