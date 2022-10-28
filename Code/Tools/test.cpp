#include <DWinRtx64Tools.h>

// ========================================== tests ====================================================
#define _TEST_BASIC_THREAD
// ========================================== tests ====================================================

void fnvTestThread();

int main() {
    #ifdef _TEST_BASIC_THREAD 
        fnvTestThread();
    #endif
}

// ========================================== functions ====================================================
_D_WRT c_RtxCMutex MutexThread1(L"Cal1");
_D_WRT c_RtxCMutex MutexMain(L"Cal1");

void fnvFunThread1(int * dptDataIO) {
    MutexThread1.fnbGetMutex();
    while(1) {
        if(MutexThread1.fnbLock()) {
            _STD cout << "Thread1: " << dptDataIO[0] << ", " << dptDataIO[1] << _STD endl;

            dptDataIO[2] += 1, dptDataIO[3] += 2;
        }
        MutexThread1.fnbUnlock();
    }
}

void fnvFunMain(int * dptDataIO) {
    while(1) {
        MutexMain.fnbUnlock();
        MutexMain.fnbLock();
        _STD cout << "Main: " << dptDataIO[2] << ", " <<  dptDataIO[3] << _STD endl << _STD endl; 

        dptDataIO[0] += 1, dptDataIO[1] += 2;

        Sleep(1000); // simulate the realtime control circle
    }
}

void fnvTestThread() {
    int dptDataIO[4];
    void (*fptFunThread)(int *) = fnvFunThread1;
    void (*fptFunMain)(int *) = fnvFunMain;

    dptDataIO[0] = dptDataIO[2] = 10;
    dptDataIO[1] = dptDataIO[3] = 20;
    
    MutexMain.fnbCreateMutex();

    _D_WRT ctm_RtxCThread<int> Thread1(fnvFunThread1, dptDataIO);
    auto cptThread1 = &Thread1;

    cptThread1->fnbCreateThread(FALSE);
    cptThread1->fnbStartThread();
    cptThread1->fnbGetAvailableProcessor();

    fptFunMain(dptDataIO);

    getchar();
}