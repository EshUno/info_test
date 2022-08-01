#include "SharedFile.h"
#include <unistd.h>
#include <iostream>

SharedFile::SharedFile(int fd): fd_(fd)
{
    dataReady_ = false;
}

void SharedFile::PutData(const std::string &str)
{
        // пытаемся взять мютекс
        std::unique_lock<std::mutex> lock(mtx_);
        
		size_t nBytes = str.size();
        const char *data = str.c_str();
        // записываем
        while (nBytes > 0)
        {
            auto nBytesWrote = write(fd_, data, nBytes);
            nBytes -= nBytesWrote;
            data += nBytesWrote;
        }

        // взводим флажок и сигнализируем другому потоку о наличии свежего чтива
        dataReady_ = true;
        cv_.notify_one();
		
}

int SharedFile::WaitAndGetData()
{
    std::string newString;
    char chunk[128];
      {
        // ставим условную переменную на ожидание
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]() { return dataReady_ == true; });
        // с этого момента мютекс снова захвачен,
        // определяем, сколько байт надо будет вычитать
        auto nBytesToRead = lseek(fd_, 0, SEEK_END);;
        // возвращаем указатель позиции в начало файла
        lseek(fd_, 0, SEEK_SET);
        // читаем кусками, вдруг за один раз не получится
        while (nBytesToRead > 0)
        {
            auto nBytesRead = read(fd_, chunk, 128);
            nBytesToRead -= nBytesRead;
            newString += std::string(chunk, nBytesRead);
        }
        // указатель файла возвращаем в начало и затираем файл
        lseek(fd_, 0, SEEK_SET);
        ftruncate(fd_, 0);
        dataReady_ = false;
    }

    std::cout << "Thr2: got string " << newString << std::endl;
    int sum = 0;
    for (size_t i = 0; i < newString.size(); ++i)
    {
         if (newString[i] >= '0' && newString[i] <= '9')
            sum += newString[i] - '0';
    }
    return sum;
}

