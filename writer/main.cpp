#include <iostream>
#include <thread>
#include <iomanip>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <condition_variable>
#include <mutex>
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include <addr.h>
#include "SharedFile.h"
#include "sharedbuf.h"

int create_tmp_file(std::string &filename)
{
    char tempFileName[] = "/tmp/cppp_writer.XXXXXX";
    int ret = mkstemp(tempFileName);
    if (ret == -1)
    {
        throw std::runtime_error("problem with file create");
    }
    filename = std::string(tempFileName);
    return ret;
}

bool all_sym_is_dig(std::string &str) // проверка, что все символы - цифры
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

bool comp (const char a, const char b)
{
    return a > b;
}

void threa_1(SharedFile &shared_file)
{
    std::string str;
    std::cout<< "Press ctrl+с for end" << std::endl;
    while (std::getline(std::cin, str))
    {
        if ((str.size() <= 64) && (all_sym_is_dig(str)))
        {
            std::sort(str.begin(), str.end(), comp);
            std::cout<<str<<std::endl;
            const std::string KB = "KB";
            std::string newString;
            for (size_t i = 0; i < str.size(); ++i)
            {
                int dig = str[i] - '0';
                if (dig % 2 == 0)
                {
                    newString += KB;
                }
                else
                {
                    newString += str[i];
                }
            }
            std::cout<<newString<<std::endl;
            shared_file.PutData(newString);
        }
        else
        std:: cout <<" Wrong string"<<std::endl;
    }
    return;
}

void threa_2(SharedFile & shared_file)
{
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    bool connected = false;

    struct sockaddr sa;
    sa.sa_family = AF_UNIX;
    strcpy(sa.sa_data, SOCKADDR_UNIX);

    int len = sizeof(sa.sa_family) + strlen(sa.sa_data);

    while (true)
    {
        int sum = shared_file.WaitAndGetData();
        std::cout<< sum <<std::endl;
        // отправляем во вторую программу
        errno = 0;
        if (!connected)
        {
            if (connect(sock, &sa, len) < 0)
                std::cout<<"Connection is not established at this time" << strerror(errno) <<std::endl;
            else
            {
                connected = true;
                errno = 0;
            }

        }
        errno = 0;
        if (connected)
        {
            if (send(sock, reinterpret_cast<void *>(&sum), sizeof(sum), 0) < 0)
                std::cout<<"Message was not send" << strerror(errno) <<std::endl;
        }
    }
    close(sock);
    return;
}


int mai()
{
    std::string filename;
    int fd;
    try {
      fd = create_tmp_file(filename);
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        std::exit(1);
    }
    SharedFile shared_file(fd);
    auto thr2 = std::thread(threa_2, std::ref(shared_file));
    threa_1(shared_file);
    thr2.join();
    close(fd);
    unlink(filename.c_str());
    return 0;
}
