#include "lib.h"
#include "MenuInit.cpp"

using namespace Flash;


int main(){


    Init(manager, parser, mainMenu, currMenu);

    currMenu = &currMenu->menus.at(2);
    currMenu->options["rangeSelect"].func("");

    return 0;
}
