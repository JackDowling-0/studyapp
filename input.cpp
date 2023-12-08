#include "lib.h"
#include "MenuInit.cpp"


namespace Flash{

void inputHandler() {

    [&] {inputLoop:
        while (true) {
            std::string input = "";
            int i = 0;

            // Print the menu
            currMenu->displayMenu();

            // Print menu options
            i = currMenu->listOptions();
            if (currMenu->menuName != "Main Menu"){
                std::cout << i << ". main: Return to main menu \n";
                i++;
            }
            std::cout << i << ". exit: Exit the program \n" << std::endl;

            // Start input loop
            std::getline(std::cin, input);

            // Check if the input matches any option
            for (const auto& option : currMenu->options){
                if (input == option.first){
                    option.second.func("");
                    goto inputLoop;
                } else if (input == "main"){
                    currMenu = &mainMenu;
                    goto inputLoop;
                } else if (input == "exit"){
                    return;
                }
            }
            std::cout << "Please select a valid option. \n";
            }
    }();

    manager.writeLibraryToStorage();
    std::cout << "Goodbye! \n";
}
}