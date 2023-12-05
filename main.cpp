#include "lib.h"
#include "MenuInit.cpp"

// int init(){
//     Flash::FlashcardManager manager;
//     Flash::Parser parser(manager);
    
//     loadMenus();
//     manager.readFromStorage();

// }

int main(){

    INIT_MENU();
    // Flash::FlashcardManager manager;
    // Flash::Parser parser(manager);

    // Menu MainMenu;
    // // Menu CardCreation = {"card creator", "create a new card", &MainMenu};
    // Menu Filler = Menu("filler", "filler", &MainMenu);
    // Menu* currMenu = &MainMenu;

    // MainMenu.addMenu(Menu("creator", "create a card", &MainMenu));
    // MainMenu.addMenu(Menu("creatorTwo", "create a card", &MainMenu));
    
    // // std::cout << "Addresses: " << &manager << " " << &parser;

    // // currMenu->displayMenu();
    // // currMenu = &currMenu->menus.at("creatorTwo");
    // // currMenu->moveMenu("creatorTwo", *currMenu);
    // currMenu->displayMenu();

    // currMenu->addAction({
    //     "create",
    //     "Create a card : with a colon-separated line",
    //     std::function<void(std::string)>([&manager, &parser](std::string s){
    //         manager.addFlashcard(parser.parseLine(s));
    //     })
    // });

    // currMenu->options["create"].func("This is: a card");
    // currMenu->options["create"].func("This is: not a card");

    // manager.displayCards();

//    manager.displayCards();

    // currMenu = MainMenu.subMenu(currMenu); // currMenu* = MainMenu.menus(0)
    // MainMenu.subMenu(currMenu);
    // currMenu->displayMenu();
    // currMenu = MainMenu.menus.at(1);
    // currMenu->displayMenu();
    


    

    return 0;
}
