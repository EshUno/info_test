#include "sharedbuf.h"
#include "thread_1.h"
#include "thread_2.h"
#include "addr.h"
#include <algorithm>
#include <signal.h>
#include <cstring>
int main()
{
    try{
            SharedBuf shared_buf;
            thread_1 thr1(shared_buf);
            thr1.start();
            thread_2 thr2(shared_buf);
            thr2.start();
            thr1.stop();
            shared_buf.stop();
            thr2.stop();
    }
    catch (std::runtime_error &e)
    {
        std::cout<< e.what () << std::endl;
    }
    return 0;
}
