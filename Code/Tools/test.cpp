#include <DWinRtx64Tools.h>

// ========================================== tests ====================================================
// #define _TEST_BASIC_THREAD
#define _TEST_IPC
// ========================================== tests ====================================================

void fnvTestThread();
void fnvTestIPC();

int main() {
    #ifdef _TEST_BASIC_THREAD 
        fnvTestThread();
    #endif
    #ifdef _TEST_IPC 
        fnvTestIPC();
    #endif
}

// ========================================== _TEST_BASIC_THREAD ====================================================
typedef struct {
    double dPos[4];
}stDataIO;

void fnvFunWin(int * nptNull) {
    _D_WRT ctm_RtxCShm<stDataIO> ShmWin(L"Shm1"); // instantiate the sharedmemory named "Shm1" in thread: win
    _D_WRT c_RtxCMutex MutexWin(L"Mutex1"); // instantiate the mutex named "Mutex1" in thread: win 
    _D_WRT c_RtxCEvent EventWin(L"Event1"); // instantiate the event named "Event1" in thread: win
    ShmWin.fnbOpen(5);
    MutexWin.fnbOpen(5);
    EventWin.fnbOpen(5);
    stDataIO DataIO;

    while(1) { // loop in win
        if(EventWin.fnbWait()) { // synchronize

            if(MutexWin.fnbLock()) DataIO = *(ShmWin.fntmptGetDataIOPointer()); // get data
            MutexWin.fnbUnlock(); // unlock

            _STD cout << "Thread1: " << DataIO.dPos[0] << ", " << DataIO.dPos[1] << _STD endl;
            DataIO.dPos[2] += 1.0, DataIO.dPos[3] += 2.0; // process the data

            if(MutexWin.fnbLock()) *(ShmWin.fntmptGetDataIOPointer()) = DataIO; // send data
            MutexWin.fnbUnlock(); // unlock
        }
    }
}

void fnvFunRtx() {
    _D_WRT ctm_RtxCShm<stDataIO> ShmRtx(L"Shm1"); // instantiate the sharedmemory named "Shm1" in thread: rtx
    _D_WRT c_RtxCMutex MutexRtx(L"Mutex1"); // instantiate the mutex named "Mutex1" in thread: rtx
    _D_WRT c_RtxCEvent EventRtx(L"Event1"); // instantiate the event named "Event1" in thread: rtx
    ShmRtx.fnbCreate();
    MutexRtx.fnbCreate();
    EventRtx.fnbCreate(3);
    stDataIO DataIO;
    DataIO.dPos[0] = DataIO.dPos[2] = 10.0;
    DataIO.dPos[1] = DataIO.dPos[3] = 20.0;
    *ShmRtx.fntmptGetDataIOPointer() = DataIO; // init data

    while(1) { // loop in rtx
        EventRtx.fnbSet(); // synchronize

        DataIO.dPos[0] += 1.0, DataIO.dPos[1] += 2.0; // obtain sensor data
        if(MutexRtx.fnbLock()) *(ShmRtx.fntmptGetDataIOPointer()) = DataIO; // send data
        MutexRtx.fnbUnlock(); // unlock

        Sleep(10);
        _STD cout << "Main: " << DataIO.dPos[2] << ", " <<  DataIO.dPos[3] << _STD endl << _STD endl; 
        Sleep(990); // simulate the realtime control circle

        if(MutexRtx.fnbLock()) DataIO = *(ShmRtx.fntmptGetDataIOPointer()); // get data
        MutexRtx.fnbUnlock(); // unlock            
    }
}

void fnvTestThread() {
    void (*fptFunWin)(int *) = fnvFunWin; // obtain the function pointder for windows
    void (*fptFunRtx)() = fnvFunRtx; // obtain the function pointder for rtx
    
    int nNull = 0;

    _D_WRT ctm_RtxCThread<int> Thread1(&nNull);
    auto cptThread1 = &Thread1;

    cptThread1->fnbCreate(fptFunWin, FALSE);
    // cptThread1->fnbGetAvailableProcessor();
    cptThread1->fnbStart();

    fptFunRtx();

    getchar();
}

// ========================================== _TEST_IPC ====================================================
void fnvIPCWin(int * nptNull) {
    _D_WRT c_RtxCEvent cEventWin(L"Even1");
    _D_WRT ctm_RtxIPC<stDataIO> ctmIPCWin(L"Cal1");
    cEventWin.fnbOpen(5);
    ctmIPCWin.fnbCreate();

    stDataIO DataIO;

    while(1) {
        cEventWin.fnbWait();

        ctmIPCWin.fnbGetData(&DataIO);
        _STD cout << "Thread2: " << DataIO.dPos[0] << ", " << DataIO.dPos[1] << _STD endl; 
        DataIO.dPos[2] += 1.0, DataIO.dPos[3] += 2.0;
        ctmIPCWin.fnbSendData(&DataIO);
    }
}

void fnvIPCRtx() {
    _D_WRT c_RtxCEvent cEventRtx(L"Even1");
    _D_WRT ctm_RtxIPC<stDataIO> ctmIPCRtx(L"Cal1");
    cEventRtx.fnbCreate(3);
    ctmIPCRtx.fnbCreate();

    stDataIO DataIO;
    DataIO.dPos[0] = DataIO.dPos[2] = 10.0;
    DataIO.dPos[1] = DataIO.dPos[3] = 20.0;

    while(1) {
        cEventRtx.fnbSet();

        DataIO.dPos[0] += 1.0, DataIO.dPos[1] += 2.0;
        ctmIPCRtx.fnbSendData(&DataIO);
        Sleep(1000);
        ctmIPCRtx.fnbGetData(&DataIO);
        _STD cout << "Main: " << DataIO.dPos[2] << ", " << DataIO.dPos[3] << _STD endl << _STD endl; 
    }
}

void fnvTestIPC() {
    int nNull = 0;

    _D_WRT ctm_RtxCThread<int> Thread2(&nNull);
    Thread2.fnbCreate(fnvIPCWin, TRUE);

    fnvIPCRtx();
}