#include "lib.h"
#include "MenuInit.cpp"

using namespace Flash;


int main(){


    Init(manager, parser, mainMenu, currMenu);
    
    currMenu = &mainMenu.menus.at(0);

    currMenu->displayMenu();
    currMenu->options["creator"].func("");

    manager.writeLibraryToStorage();
    return 0;
}
