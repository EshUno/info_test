#ifndef THREAD_1_H
#define THREAD_1_H

#include "sharedbuf.h"
#include <thread>

class thread_1
{
public:
    thread_1(SharedBuf &buf);
    ~thread_1();
    void start();
    void stop();

private:
    //канал - используется для сигнала остановки с терминала
    int pipe_fd[2];
    SharedBuf &shared_buf;
    std::thread thr1;
    const std::string KB = "KB";
    void work();
    bool work_getline(std::string &data);
    bool all_sym_is_digit(std::string &data);
    void convert_string(std::string &data);
};

#endif // THREAD_1_H
