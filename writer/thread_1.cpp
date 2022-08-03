#include "thread_1.h"
#include <algorithm>
#include <unistd.h>
#include <cstring>
#include <poll.h>

thread_1::thread_1(SharedBuf &buf): shared_buf(buf)
{

}

thread_1::~thread_1()
{

}

void thread_1::start()
{
    errno = 0;
    if (pipe(pipe_fd))
    {
        throw std::runtime_error(std::string("thread_1: ") + strerror(errno));
    }
    thr1 = std::thread(&thread_1::work, this);
}

void thread_1::work()
{
    std::string data;
    std::cout<< "Press ctrl+с for end" << std::endl;
    while (!work_getline(data))
    {
        if (!(data.size() <= 64) || !(all_sym_is_digit(data)))
            std::cout<<"Wrong string"<<std::endl;
        else
        {
            std::sort(data.begin(), data.end(),
                      [](auto a, auto b){ return a > b;});
            std::string ans;
            for(auto &symbol: data)
            {
                int dig = symbol - '0';
                if (dig % 2)
                {
                    ans += symbol;
                }
                else
                {
                    ans += KB;
                }
            }
            shared_buf.put_data(ans);
        }
    }
}

bool thread_1::work_getline(std::string &input)
{
    // опрашиваются 2 дескриптора - 0 на пользовательский ввод,
    // 1 - на признак окончания
    struct pollfd pfds[2];
    pfds[0] = {STDIN_FILENO, POLLIN, 0};
    pfds[1] = {pipe_fd[0],POLLIN, 0};
    input.clear();
    int ret = 0;
    errno = 0;
    while(ret == 0){
        ret = poll(pfds, 2, 100);
        if (ret > 0)
        {
            //если что-то пришло по дескриптору 1 - значит пора остановиться
            // а если на 0 - значит пришла новая строка
            if (pfds[1].revents & POLLIN) return true;
            if (pfds[0].revents & POLLIN)
            {
                std::getline(std::cin, input);
                break;
            }
        }
        else if(ret == -1)
        {
            throw std::runtime_error(std::string("thread_1: ") + strerror(errno));
        }
    }
    return false;

}

void thread_1::stop()
{
    char byte = 0x42;
    write(pipe_fd[1], &byte, sizeof(byte));

    if (thr1.joinable())
        thr1.join();

    close(pipe_fd[0]);
    close(pipe_fd[1]);
}

bool thread_1::all_sym_is_digit(std::string &data)
{
    for (auto &symbol: data)
    {
        if (!isdigit(symbol)) return false;
    }
    return true;
}
