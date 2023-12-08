#include "lib.h"
#include "input.cpp"

using namespace Flash;

int main(){

    Init(manager, parser, mainMenu, currMenu);
    
    inputHandler(currMenu);

    return 0;
}
