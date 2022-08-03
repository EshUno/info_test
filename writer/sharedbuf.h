#ifndef SHAREDBUF_H
#define SHAREDBUF_H

#include <condition_variable>
#include <mutex>
#include <string>
#include <iostream>
#include <queue>

class SharedBuf final
{
public:
    SharedBuf();
    // помещаем данные в общий буфер в 1 потоке и уведомляем, что они там появились
    void put_data(const std::string &str);
    // забираем данные из общего буфера во 2 потоке и передаем их для отправки
    // возвращает пустую строку, если 1 поток  остановился и нужно остановить 2
    std::queue<std::string> wait_and_get_data();
    //взводим условную переменную, по которой 2 поток понимает, что должен остановиться
    void stop();

private:
    //очередь для передачи обработанных 1 потоком данных во 2 поток
    std::queue<std::string> buff;
    bool stopped;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif // SHAREDBUF_H
