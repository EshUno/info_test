#ifndef THREAD_2_H
#define THREAD_2_H

#include "sharedbuf.h"
#include <thread>
#include <arpa/inet.h>

class thread_2
{
public:
    thread_2(SharedBuf &buf);
    ~thread_2();
    void start();
    void stop();

private:
    void work();
    void thr_connect();
    void thr_connect_stop();
    void addr_fill();
    void push_sum(int sum);
    int count_sum(std::string &buff_elem);
    void create_socket();

    SharedBuf &shared_buf;
    std::thread thr2;
    std::thread thr3;
    int sock;
    struct sockaddr_in addr;
    std::queue<int> shared_sum;
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> stopped;

};

#endif // THREAD_2_H
