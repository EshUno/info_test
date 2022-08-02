#ifndef THREAD_1_H
#define THREAD_1_H

#include "sharedbuf.h"
#include <string>
#include <iostream>
#include <thread>

class thread_1
{
public:
    thread_1(SharedBuf &buf);
    ~thread_1();
    void start_thr1();
    void stop_thr1();

private:
    void work();
    SharedBuf &shared_buf;
    std::thread thr1;
    const std::string KB = "KB";
    bool all_sym_is_digit(std::string &data);
};

#endif // THREAD_1_H
