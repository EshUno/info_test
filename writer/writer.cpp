#include "sharedbuf.h"
#include <algorithm>
#include <thread>
#include <signal.h>

bool all_sym_id_digit(std::string &data)
{
    for (auto &symbol: data)
    {
        if (!isdigit(symbol)) return false;
    }
    return true;
}

/*static void sig_handler(int sig)
{

}*/

void thread_1(SharedBuf &shared_buf)
{
    std::string data;
    const std::string KB = "KB";
    std::cout<< "Press ctrl+с for end" << std::endl;
    while (std::getline(std::cin, data))
    {
        if ((data.size() <= 64) && (all_sym_id_digit(data)))
        {
            std::cout<<data<<std::endl;
            std::sort(data.begin(), data.end(), [](auto a, auto b){ return a > b;});
            std::cout<<data<<std::endl;
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
            std::cout<<ans<<std::endl;
        }
        else std::cout<<"Wrong string"<<std::endl;
    }
    return;
}

void thread_2(SharedBuf &shared_buf)
{




    return;
}

int main()
{
    SharedBuf shared_buf;
    auto thr1 = std::thread(thread_1, std::ref(shared_buf));
 //   auto thr2 = std::thread(thread_2, std::ref(shared_buf));

 /*   if(signal(SIGINT, sig_handler) == SIG_ERR)
       std::cerr<< "signal processing" << std::endl;
    if(signal(SIGTERM, sig_handler) == SIG_ERR)
       std::cerr<< "signal processing" << std::endl;
*/
    thr1.join();
 //   thr2.join();
    return 0;
}
