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
void fnvFunWin(int * dptDataIO) {
    _D_WRT c_RtxCMutex MutexWin(L"Cal1"); // instantiate the mutex named "Cal1" in thread: win 
    MutexWin.fnbOpen();
    

    while(1) { // loop in win
        if(MutexWin.fnbLock()) {
            _STD cout << "Thread1: " << dptDataIO[0] << ", " << dptDataIO[1] << _STD endl;

            dptDataIO[2] += 1, dptDataIO[3] += 2;
        }
        MutexWin.fnbUnlock();
    }
}

void fnvFunRtx(int * dptDataIO) {
    _D_WRT c_RtxCMutex MutexRtx(L"Cal1"); // instantiate the mutex named "Cal1" in thread: rtx
    MutexRtx.fnbCreate();

    while(1) { // loop in rtx
        if(MutexRtx.fnbLock()) {
            _STD cout << "Main: " << dptDataIO[2] << ", " <<  dptDataIO[3] << _STD endl << _STD endl; 

            dptDataIO[0] += 1, dptDataIO[1] += 2;

            Sleep(1000); // simulate the realtime control circle
        }
        MutexRtx.fnbUnlock();
    }
}

void fnvTestThread() {
    void (*fptFunWin)(int *) = fnvFunWin; // obtain the function pointder for windows
    void (*fptFunRtx)(int *) = fnvFunRtx; // obtain the function pointder for rtx
    
    _D_WRT ctm_RtxCShm<int> Shm1(L"Shm1"); // instantiate the sharedmemory named "Cal1"
    auto cptShm1 = &Shm1; // obtain the sharedmemory pointer
    
    cptShm1->fnbCreateShm(); // sharedmemory: create
    *cptShm1->fntmptGetDataIOPointer() = *(cptShm1->fntmptGetDataIOPointer() + 2) = 10; // init the data
    *(cptShm1->fntmptGetDataIOPointer() + 1) = *(cptShm1->fntmptGetDataIOPointer() + 3) = 20; // init the data
    
    _D_WRT ctm_RtxCThread<int> Thread1(cptShm1->fntmptGetDataIOPointer());
    auto cptThread1 = &Thread1;

    cptThread1->fnbCreate(fptFunWin, FALSE);
    cptThread1->fnbGetAvailableProcessor();
    cptThread1->fnbStart();

    fptFunRtx(cptShm1->fntmptGetDataIOPointer());

    getchar();
}
