#ifndef _RT_NEW_HH_
#define _RT_NEW_HH_

#include <cstddef>

extern "C" void *rt_malloc(unsigned int size);
extern "C" void rt_free(void *p);

void* operator new(size_t);
void* operator new [](size_t);
void  operator delete(void*);
void  operator delete [](void*);

#endif // _RT_NEW_HH_

