#ifndef MENUS_H
#define MENUS_H

#include <map>
#include <functional>
#include <typeinfo>

//forward declaration
class Menu;

//options class
class Options {
    public:
        Options(const std::string& optionName, Menu& nextMenu) : optionName(optionName), nextMenu(&nextMenu){}

        const std::string& GetOptionName() const {
            return optionName;
        }

    private:
        std::string optionName;
        //menu the option points to
        Menu* nextMenu;
};

//base Menu class
class Menu {
    public:
        Menu (const std::string& menuName = "Main Menu", Menu* prevMenu = nullptr) : menuName(menuName){}

        virtual void displayMenu() const {
            std::cout << "Current menu: " << menuName << std::endl;
            // std::cout << "Options: " << std::endl;

            // for (const auto& option : options) {
            //     std::cout << option.GetOptionName() << std::endl;
            // }
        }

        // void addOption(const std::string& optionName, Menu& nextMenu){
        //     options.emplace_back(optionName, nextMenu);
        // }

        void addMenu(Menu* menu){
            menu->prevMenu = this;
            menus.push_back(menu);
        }

        Menu* getPrevMenu(){
            return prevMenu;
        }

        //display all menus
        void displayAllMenus(){
            std::cout << "Current Menu: " << menuName << std::endl;
            for (const auto &m : menus){
                std::cout << "Sub Menu: " << m->menuName << std::endl;
            }
        }

        Menu* subMenu(Menu* currMenu){
            currMenu = menus.at(0);
            return currMenu;
        }

    private:
        Menu* prevMenu = this;
        const std::string menuName;
        std::vector<Options> options;
        std::vector<Menu*> menus;
        
};



#endif