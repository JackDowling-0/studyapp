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
            int m = 0;
            int e = 0;
            if (currMenu->menuName != "Main Menu"){
                std::cout << i << ". main: Return to main menu \n";
                m = i;
                i++;
            }
            std::cout << i << ". exit: Exit the program \n" << std::endl;
            e = i;

            // Start input loop
            std::getline(std::cin, input);

            // Check if the input matches any option
            for (const auto& option : currMenu->options){
                if (stoi(input) <= currMenu->options.size() - 1){
                    currMenu->options.at(stoi(input)).func("");
                    goto inputLoop;
                } else if (input == option.optionName){
                    option.func("");
                    goto inputLoop;
                } else if (input == "main" || stoi(input) == m){
                    currMenu = &mainMenu;
                    goto inputLoop;
                } else if (input == "exit" || stoi(input) == e){
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