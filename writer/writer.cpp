#include "sharedbuf.h"
#include "thread_1.h"
#include "thread_2.h"
#include "addr.h"
#include <algorithm>
#include <signal.h>
#include <cstring>

void block_mask_fill(sigset_t &block_mask)
{
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGTERM);
    sigaddset(&block_mask, SIGQUIT);
}

int main()
{
    try{
        /*
         * Устанавливыаем сигнальную маску
         Для того чтобы заблокировать доставку сигналов на всех потоках, а потом
         приостановить выполнение главного потока до момента пока один сигналов не
         будет "пойман" функцией sigwait(). Это нужно для того, чтобы обеспечить
         корректное завершение программы - закрыртие всех тредов, сокетов и каналов.
        */
        sigset_t block_mask;
        block_mask_fill(block_mask);
        errno = 0;
        if (pthread_sigmask(SIG_SETMASK, &block_mask, nullptr) != 0)
        {
          throw std::runtime_error(std::string("main_thread: ") + strerror(errno));
        }
        else
        {
            SharedBuf shared_buf;
            // все потоки унаследуют сигнальную маску
            thread_1 thr1(shared_buf);
            thr1.start();
            thread_2 thr2(shared_buf);
            thr2.start();
            int sig;
            // ожидаем, пока не придет один из сигналов, за которыми мы следим
            if(sigwait(&block_mask, &sig) != 0)
            {
                throw std::runtime_error(std::string("main_thread: ") + strerror(errno));
            }
            std::cout << "sig: " << sig << std::endl;
            /* получив сигнал, начинаем процедуру останоки потоков
             * для этого:
             * для первого потока: передаем байт, информирующий о завершении через канал
             *   (канал нужен т.к. необходимо прервать работу getlain() по ctrl+С , котороая
             *    не прервется сама т.к. мы заблокировали этот сигнал для потоков)
             * в общем буфере: меняем флаг остановки в разделяемой памяти, на которую ориентирируется второй поток
             * для второго потока: сообщаем потоку, ответственному за соединение, что он должен остановиться
             *
             */
            thr1.stop();
            shared_buf.stop();
            thr2.stop();
        }
    }
    catch (std::runtime_error &e)
    {
        std::cout<< e.what () << std::endl;
    }
    return 0;
}
