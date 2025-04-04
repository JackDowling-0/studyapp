#ifndef UTILITY_H
#define UTILITY_H

#if         !defined(_MSC_VER)
#include    <unistd.h>
#endif      // _MSC_VER for unix command utils



inline void clear_screen(){
#if defined(_MSC_VER)
    system("cls");
#else //not msvc?
    system("clear");
#endif

}



#endif
