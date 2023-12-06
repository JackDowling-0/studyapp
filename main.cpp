#include "lib.h"
#include "MenuInit.cpp"

using namespace Flash;
FlashcardManager manager;
Parser parser(manager);

Menu mainMenu;

Menu* currMenu = &mainMenu;

int main(){


    Init(manager, parser, mainMenu, currMenu);



    return 0;
}
