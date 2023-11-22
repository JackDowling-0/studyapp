#include <iostream>
#include <vector>
#include <conio.h>

#include "flashcards.h"
#include "menus.h"
 
// instantiate menus



int runInitialSetup(){

    Menu MainMenu("Main Menu");
    Menu subMenu_1("sub menu 1");
    Menu subMenu_2("sub menu 2");

    MainMenu.addOption("option 1", subMenu_1);
    MainMenu.addOption("option 2", subMenu_2);

    
    MainMenu.addFunction("Say Cheese", []() {
        std::cout << "CHeeeeese!" << std::endl;
    });
    MainMenu.executeFunction("Say Cheese");

    MainMenu.displayMenu();

    //no issues
    return 0;
}

int main(){

    runInitialSetup();

    return 0;
}
