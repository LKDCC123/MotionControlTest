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
void fnvFun1(int * dptDataIO) {
    while(1) {
        Sleep(1000);
        _STD cout << "Thread1: " << dptDataIO[0] << ", " << dptDataIO[1] << _STD endl;

        dptDataIO[2] += 1, dptDataIO[3] += 2;
    }
}

void fnvTestThread() {
    int dptDataIO1[4];
    void (*Fun1)(int *) = fnvFun1;

    dptDataIO1[0] = dptDataIO1[2] = 10;
    dptDataIO1[1] = dptDataIO1[3] = 20;

    _D_WRT ctm_RtxCThread<int> Thread1(Fun1, dptDataIO1);
    auto cptThread1 = &Thread1;

    cptThread1->fnbCreateThread(FALSE);
    cptThread1->fnbStartThread();
    cptThread1->fnbGetAvailableProcessor();

    while(1) {
        Sleep(1000);
        _STD cout << "Main: " << dptDataIO1[2] << ", " <<  dptDataIO1[3] << _STD endl << _STD endl; 

        dptDataIO1[0] += 1, dptDataIO1[1] += 2;
    }
}