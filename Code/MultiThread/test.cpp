#include<iostream>
#include<windows.h>
#include<string.h>

using namespace std;
// 互斥锁
HANDLE hMutex = CreateMutex(
    NULL,           // 没用
    FALSE,          // 资源是否属于创建它的进程
    TEXT("screen")  // 互斥锁名字
);

// 回调函数
DWORD WINAPI fnnCallBack(LPVOID lpParam) {
    while(1) {
        WaitForSingleObject(hMutex, INFINITE); // 等待hMutex被Main进程释放，无限期等待
        cout << " CallBack! " << endl;
        Sleep(2000);
        ReleaseMutex(hMutex); // 释放hMutex，hMutex将不再属于hThread进程
    }
    return 0;
}

// 主函数
int fnnA() {
    HANDLE hThread;
    DWORD dwThreadId;
    hThread = CreateThread( // 开辟线程 hThread
        NULL,               // 默认安全属性
        NULL,               // 默认堆栈大小
        fnnCallBack,        // 线程入口函数地址
        NULL,               // 传递给线程函数的参数
        0,                  // 指定线程立即运行
        &dwThreadId         // 线程ID号
    );

    while(1) {
        WaitForSingleObject(hMutex, INFINITE); // 等待hMutex被hThread进程释放，无限期等待
        cout << " Main! " << endl;
        Sleep(1000);
        ReleaseMutex(hMutex); // 释放hMutex，hMutex将不在属于Main进程
    }
    return 0;
}

int main() {
    fnnA();
    return 0;
}