#ifndef UTILITY_H
#define UTILITY_H




inline void clear_screen(){
#if defined(_MSC_VER)
    system("cls");
#else //not msvc?
    system("clear");
#endif

}



#endif
