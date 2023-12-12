#ifndef MYCLASS_H
#define MYCLASS_H

#include <windows.h>
#include <mutex>

class MyClass {
public:
    MyClass();
    ~MyClass();

    int myArray[4];  // 크기가 4인 int 배열을 public으로 선언

private:
    HANDLE thread_;
    std::mutex arrayMutex;  // 배열에 접근할 때 사용할 mutex

    static DWORD WINAPI ThreadFunction(LPVOID lpParam);
};

#endif  // MYCLASS_H