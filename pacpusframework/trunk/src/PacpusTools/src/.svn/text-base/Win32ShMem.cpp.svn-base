// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
/// @author  Gerald Dherbomez <firstname.surname@utc.fr>
/// @date    January, 2007
// %pacpus:license}

#include <Pacpus/PacpusTools/Win32ShMem.h>
#include <Pacpus/kernel/Log.h>

#include <sstream>
#include <windows.h>

DECLARE_STATIC_LOGGER("pacpus.core.Win32ShMem");

using namespace pacpus;
using namespace std;

//////////////////////////////////////////////////////////////////////////
/// Constructor
Win32ShMem::Win32ShMem(const char * name, int size)
{
    // semaphore name
    stringstream semaphoreNameSs;
    semaphoreNameSs << (const char *) "SemShMem_" << name;
    string semaphoreName = semaphoreNameSs.str();
    // event name
    stringstream eventNameSs;
    eventNameSs << (const char *) "EvtShMem_" << name;
    string eventName = eventNameSs.str();

    LOG_DEBUG("semaphore name = " << semaphoreName);
    LOG_DEBUG("event name = " << eventName);

    semaphore_ = CreateSemaphore(NULL, /* lInitialCount = */ 1, /* lMaximumCount = */ 1, semaphoreName.c_str());
    if (semaphore_ == NULL) {
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            /* flags = */ FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            /* source = */ NULL,
            /* messageId = */ dw,
            /* languageId = */ MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            /* out buffer = */ (LPTSTR) &lpMsgBuf,
            /* size = */ 0,
            /* args = */ NULL
            );

        LOG_FATAL("cannot create semaphore protection of shared memory segment '" << name << "'"
            << ". Error: " << GetLastError()
            << ". Message: " << (const char *) lpMsgBuf
            << ". Program will exit"
            ); 
        ::exit(-1); 
    }

    // create the event - autoreset mode
    event_ = CreateEvent(NULL, false, false, eventName.c_str()); 

    // lock the semaphore and try to create the shared memory
    lockMemory(); 
    shMemHandle_ = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,	PAGE_READWRITE,	0, size, name);  
    if (shMemHandle_ == NULL) {
        LOG_FATAL("cannot create shared memory segment '" << name << "'"
            << ". Error: " << GetLastError()
            << ". Program will exit"
            ); 
        ::exit(-1);
    }

    // Map the memory to a local pointer
    shMem_ = MapViewOfFile(shMemHandle_, FILE_MAP_ALL_ACCESS, 0, 0, 0); 
    if (shMem_ == NULL) {
        LOG_FATAL("cannot map the view of file of the shared memory segment '" << name << "'"
            << ". Error: " << GetLastError()
            << ". Program will exit"
            ); 
        ::exit(-1);
    }

    LOG_INFO("created Win32 shared memory '" << name << "'"); 

    unlockMemory(); 
}

//////////////////////////////////////////////////////////////////////////
/// Destructor
Win32ShMem::~Win32ShMem()
{
    // free the semaphore 
    CloseHandle(semaphore_); 
    UnmapViewOfFile(shMem_); 
    CloseHandle(shMemHandle_); 
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to wait the incoming of new data
/// you can specify a timeout in ms to avoid infinite blocking or 0 (infinite)
/// @returns @b true if new data available before the timeout, @b false otherwise
bool Win32ShMem::wait(unsigned long timeout /* = 0 */)
{
    if (timeout == 0) {
        timeout = INFINITE; 
    }

    DWORD status = 0; 
    status = WaitForSingleObject(event_, timeout); 

    if (status == WAIT_OBJECT_0) {
        return true; 
    } else {
        return false; 
    }
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to get a pointer to data of the shared memory
void * Win32ShMem::read()
{
    void * shMem; 
    lockMemory(); 
    shMem = shMem_; 
    unlockMemory(); 
    return shMem; 
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to get a pointer to data of the shared memory
void Win32ShMem::read(void * mem, int size)
{
    lockMemory(); 
    memcpy(mem,shMem_,size); 
    unlockMemory(); 
}

//////////////////////////////////////////////////////////////////////////
/// Return the event handle under Windows 
void * Win32ShMem::getEventIdentifier()
{
    return event_; 
}

//////////////////////////////////////////////////////////////////////////
/// Use this method to write data in shared memory. Offset is given in bytes
void Win32ShMem::write(void *data, int size, unsigned long offset)
{
    lockMemory(); 
    //unsigned long * dest = (unsigned long *)shMem_ + offset;
    char * dest = (char *)shMem_ + offset;
    //printf("adresses : shm : %x  dest : %x   offset : %x \n",shMem_, dest, offset); 
    memcpy(dest, data, size);
    unlockMemory();
    SetEvent(event_); 
}

//////////////////////////////////////////////////////////////////////////
/// Function that locks access to the shared memory
void Win32ShMem::lockMemory()
{
    WaitForSingleObject(semaphore_, INFINITE); 
}

//////////////////////////////////////////////////////////////////////////
/// Function that unlocks access to the shared memory
void Win32ShMem::unlockMemory()
{
    ReleaseSemaphore(semaphore_, 1, NULL); 
}
