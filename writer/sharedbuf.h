#ifndef SHAREDBUF_H
#define SHAREDBUF_H

#include <condition_variable>
#include <mutex>
#include <string>
#include <iostream>
#include <queue>
#include <atomic>

class SharedBuf final
{
public:
    SharedBuf();
    void put_data(const std::string &str);
    std::queue<std::string> wait_and_get_data();
    void stop();

private:
    //очередь для передачи обработанных 1 потоком данных во 2 поток
    std::queue<std::string> buff;
    std::atomic<bool> stopped;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif // SHAREDBUF_H
