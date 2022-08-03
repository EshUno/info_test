#ifndef THREAD_2_H
#define THREAD_2_H

#include "sharedbuf.h"
#include <thread>
#include <arpa/inet.h>

class thread_2
{
public:
    //передаем ссылку на разделяемый буфер в конструктор
    thread_2(SharedBuf &buf);
    ~thread_2();
    void start();
    void stop();

private:
    void work();
    void thr_connect();
    SharedBuf &shared_buf;
    std::thread thr2;
    std::thread thr3;
    int sock;
    struct sockaddr_in addr;

    std::queue<int> shared_sum;
    std::mutex mtx;
    std::condition_variable cv;
    bool stopped;

};

#endif // THREAD_2_H
