#ifndef THREAD_1_H
#define THREAD_1_H

#include "sharedbuf.h"
#include <thread>

class thread_1
{
public:
    //передаем ссылку на разделяемый буфер в конструктор
    thread_1(SharedBuf &buf);
    ~thread_1();
    //запуск канала и потока
    void start();
    //остановка 1 потока, закрытие канала
    void stop();

private:
    //канал - используется для сигнала остановки с терминала
    int pipe_fd[2];
    SharedBuf &shared_buf;
    std::thread thr1;
    const std::string KB = "KB";
    //ввод строки пользователем, преобразование строки и помещение в общую память
    void work();
    //чтение с 2 дескрипторов
    bool work_getline(std::string &data);
    //проверка входной строки
    bool all_sym_is_digit(std::string &data);
};

#endif // THREAD_1_H
