#include <iostream>
#include <vector>

#include "flashcards.h"
#include "menus.h"
 
// instantiate menus
Menu mainMenu("Main Menu");
Menu flashcardCreator("Flashcard Creator");
Menu flashcardRemover("Flashcard Remover");
Menu flashcardUpdater("Flashcard Updator");
Menu addLine("Add Line");

/*
example function to show menu traversal
function will initialize a pointer to the top level menu, add sub menus, 
and display the current menu at each step of the way
*/
void exampleTraversal(){

        //Initialize pointer to top level menu
        Menu* currMenu = &mainMenu; // 0x7ff73fc99040
        currMenu->displayMenu(); 

        //add sub menu
        currMenu->addMenu(&flashcardCreator);

        //add second sub menu option
        currMenu->addMenu(&flashcardRemover);

        //enter sub menus
        currMenu = currMenu->subMenu(currMenu); // 0x7ff73fc990a0

        currMenu->displayMenu();

        currMenu->addMenu(&addLine);

        //enter next sub menu
        currMenu = currMenu->subMenu(currMenu); // 0x7ff646e391c0 // deepest menu

        currMenu->displayMenu();
        
        //return pointer to previous menu
        currMenu = currMenu->getPrevMenu(); // 0x7ff646e390a0

        currMenu->displayMenu();

        currMenu = currMenu->getPrevMenu(); // 0x7ff646e39040
        currMenu->displayMenu();
}

int main(){

    exampleTraversal();

    
    return 0;
}
