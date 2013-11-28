// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}

#ifdef WIN32
  #include <windows.h>
#endif

#include <Pacpus/kernel/road_time.h>

#include <memory.h> 
#include <sys/types.h>
#include <sys/timeb.h>
#include <malloc.h>



#define SHMEMSIZE sizeof(struct Initialisation_Time) 
 
static LPVOID lpvMem = NULL; // pointer to shared memory

VOID SetSharedMem(struct Initialisation_Time * toto);
VOID GetSharedMem(struct Initialisation_Time * toto);

BOOL WINAPI DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	HANDLE hMapObject = NULL;  // handle to file mapping
    BOOL fInit, fIgnore; 
	struct Initialisation_Time First_Launcher;
	struct timeb timeptr;
	LARGE_INTEGER tmp;

    switch (ul_reason_for_call)
	{
		case DLL_THREAD_ATTACH:
			break;
		case DLL_PROCESS_ATTACH:
			// Create a named file mapping object.
            hMapObject = CreateFileMapping( 
                INVALID_HANDLE_VALUE, // use paging file
                NULL,                 // default security attributes
                PAGE_READWRITE,       // read/write access
                0,                    // size: high 32-bits
                SHMEMSIZE,            // size: low 32-bits
                "roadtimedllmemfilemap");     // name of map object
            if (hMapObject == NULL) 
                return FALSE; 
 
            // The first process to attach initializes memory.
 
            fInit = (GetLastError() != ERROR_ALREADY_EXISTS); 
 
            // Get a pointer to the file-mapped shared memory.
 
            lpvMem = MapViewOfFile( 
                hMapObject,     // object to map view of
                FILE_MAP_WRITE, // read/write access
                0,              // high offset:  map from
                0,              // low offset:   beginning
                0);             // default: map entire file
            if (lpvMem == NULL) 
                return FALSE; 
 
            // Initialize memory if this is the first process.
            if (fInit) 
				{
					memset(lpvMem, '\0', SHMEMSIZE); 
					
					ftime(&timeptr );
					First_Launcher.Real_Time=(road_time_t) timeptr.time * 1000000 +(road_time_t) timeptr.millitm * 1000;
					if (!QueryPerformanceFrequency(&tmp))
						{
							MessageBox(NULL,"No Multimedia Counter Available","DLL Message",MB_OK);
							First_Launcher.Multimedia_Counter_Frequency=(unsigned __int64) 0;
							First_Launcher.Multimedia_Counter=(unsigned __int64)0;
							First_Launcher.delta_t=First_Launcher.Real_Time;
							SetSharedMem(&First_Launcher);
							return FALSE;
						}	
					First_Launcher.Multimedia_Counter_Frequency=(unsigned __int64) tmp.QuadPart;
					if (!QueryPerformanceCounter(&tmp))
						{	
							MessageBox(NULL,"Couldn't Get the value of Multimedia Counter","DLL Message",MB_OK);
							First_Launcher.Multimedia_Counter_Frequency=(unsigned __int64) 0;
							First_Launcher.Multimedia_Counter=(unsigned __int64)0;
							First_Launcher.delta_t=First_Launcher.Real_Time;
							SetSharedMem(&First_Launcher);
							return FALSE;
						}
					First_Launcher.Multimedia_Counter=(unsigned __int64)tmp.QuadPart;
					First_Launcher.delta_t=First_Launcher.Real_Time-(road_time_t) (First_Launcher.Multimedia_Counter*1000000/First_Launcher.Multimedia_Counter_Frequency);
					//MessageBox(NULL,"You called Road_Time_2.DLL","DLL Message",MB_OK);
					SetSharedMem(&First_Launcher);


				}
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			 // Unmap shared memory from the process's address space.
			 // In the case of the last process, Windwos automatically clean up the memory.
             fIgnore = UnmapViewOfFile(lpvMem); 
             // Close the process's handle to the file-mapping object.
             fIgnore = CloseHandle(hMapObject); 
			break;
    }
    return TRUE;
}


// SetSharedMem sets the contents of shared memory. 
VOID SetSharedMem(struct Initialisation_Time * toto) 
{ 
    // Copy the null-terminated string into shared memory.
 
    memcpy(lpvMem,toto,sizeof(struct Initialisation_Time));
} 
 
// GetSharedMem gets the contents of shared memory. 
VOID GetSharedMem(struct Initialisation_Time * toto) 
{ 
    memcpy(toto,lpvMem,sizeof(struct Initialisation_Time));
}


// This is an example of an exported function.
road_time_t ROAD_TIME_API road_time2(void)
{
	struct Initialisation_Time First_Launcher;
	road_time_t reply;
	LARGE_INTEGER tmp;
	struct timeb timeptr;
	
	GetSharedMem(&First_Launcher);

	if (!QueryPerformanceCounter(&tmp))
		{	
			MessageBox(NULL,"Couldn't Get the value of Multimedia Counter","DLL Message",MB_OK);
			ftime(&timeptr );
			reply=(road_time_t) timeptr.time * 1000000 +(road_time_t) timeptr.millitm * 1000;
		}
					
	else
		{	
			reply=(road_time_t) First_Launcher.Real_Time + (road_time_t) (((unsigned __int64) tmp.QuadPart - First_Launcher.Multimedia_Counter) * 1000000/First_Launcher.Multimedia_Counter_Frequency);
		}
	return(reply);

}

// This is an example of a second exported function.
road_time_t ROAD_TIME_API road_time(void)
{
	struct Initialisation_Time First_Launcher;
	road_time_t reply;
	LARGE_INTEGER tmp;
	struct timeb timeptr;
	
	GetSharedMem(&First_Launcher);
	
	if (!QueryPerformanceCounter(&tmp))
		{	
			MessageBox(NULL,"Couldn't Get the value of Multimedia Counter","DLL Message",MB_OK);
			ftime(&timeptr );
			reply=(road_time_t) timeptr.time * 1000000 +(road_time_t) timeptr.millitm * 1000;
		}
					
	else
		{	
			reply=First_Launcher.delta_t+(road_time_t) ((tmp.QuadPart*1000000)/First_Launcher.Multimedia_Counter_Frequency);
			
		}
	return(reply);

}

// This is an example of a second exported function.
struct Initialisation_Time ROAD_TIME_API road_time_init(void)
{
	struct Initialisation_Time First_Launcher;
	
	GetSharedMem(&First_Launcher);
	return(First_Launcher);

}