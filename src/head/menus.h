#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <limits>

struct Menu {
    std::string menuName;
    std::vector<std::string> options;

    Menu(const std::string& name, const std::vector<std::string>& opts) 
        : menuName(name), options(opts) {}

    void displayMenu() {
        std::cout << menuName << "\n";
        for (size_t i = 0; i < options.size(); ++i){
            std::cout << "  " << i + 1 << ". " << options[i] << "\n";
        } std::cout << std::endl;
    }
};

//menus
void const MainMenu();
void const PracticeMenu();
void const CreateMenu();
void const RemoveMenu();
void const exit_program();
void const promptWizard();
#endif