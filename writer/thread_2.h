#ifndef THREAD_2_H
#define THREAD_2_H

#include "sharedbuf.h"
#include <thread>

class thread_2
{
public:
    thread_2(SharedBuf &buf);
    ~thread_2();
    void start();
    void stop();

private:
    void work();
    SharedBuf &shared_buf;
    std::thread thr2;
};

#endif // THREAD_2_H
