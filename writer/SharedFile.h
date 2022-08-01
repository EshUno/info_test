#ifndef SHARED_FILE_H
#define SHARED_FILE_H

#include <string>
#include <condition_variable>
#include <mutex>

class SharedFile final
{
public:
    SharedFile(int fd);
    void PutData(const std::string &str);
    int WaitAndGetData();

private:
    int fd_;
    bool dataReady_;
    std::mutex mtx_;
    std::condition_variable cv_;
};

#endif
