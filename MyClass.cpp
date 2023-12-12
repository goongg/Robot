#include "MyClass.h"
#include <iostream>

MyClass::MyClass() {
    // 생성자에서 1ms 주기로 실행되는 스레드 시작
    thread_ = CreateThread(NULL, 0, &MyClass::ThreadFunction, this, 0, NULL);
    if (thread_ == NULL) {
        std::cerr << "Failed to create thread" << std::endl;
    }

    while(1);
}

MyClass::~MyClass() {
    // 소멸자에서 스레드 종료
    if (thread_ != NULL) {
        CloseHandle(thread_);
    }
}

DWORD WINAPI MyClass::ThreadFunction(LPVOID lpParam) {
    MyClass* instance = static_cast<MyClass*>(lpParam);
    while (true) {
        // 1ms 대기
        Sleep(1);

        // 배열에 접근할 때 mutex 사용
        std::lock_guard<std::mutex> lock(instance->arrayMutex);

        // 배열의 모든 값에 1씩 증가
        for (int i = 0; i < 4; ++i) {
            instance->myArray[i]++;
        }

        // 스레드에서 수행할 작업 추가
        std::cout << "Thread running every 1ms" << std::endl;
        
        // 배열의 현재 상태 출력
        std::cout << "Array values: ";
        for (int i = 0; i < 4; ++i) {
            std::cout << instance->myArray[i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

int main()
{
    MyClass m;

    while(1);
}