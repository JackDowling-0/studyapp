#ifndef MENUS_H
#define MENUS_H

#include <map>
#include <functional>
//forward declaration
class Menu;

//options class
struct Option {
    std::string optionName;
    std::string optionDescription;
    std::function<void(std::string)> func;

    Option(std::string optionName = "", std::string optionDescription = "", std::function<void(std::string)> func = std::function<void(std::string)>([](std::string s = ""){})) : optionName(optionName), optionDescription(optionDescription), func(func){}

        
};

//base Menu class
class Menu {
    public:
        Menu (std::string menuName = "Main Menu", std::string description = "Main Menu", Menu* prevMenu = nullptr) : menuName(menuName), description(description), prevMenu(prevMenu){}

        virtual void displayMenu() const {
            std::cout << "Current menu: " << menuName << "\n";
            std::cout << "'" << description << "'" << std::endl;
            // std::cout << "Options: " << std::endl;

            // for (const auto& option : options) {
            //     std::cout << option.GetOptionName() << std::endl;
            // }
        }

        // void addOption(const std::string& optionName, Menu& nextMenu){
        //     options.emplace_back(optionName, nextMenu);
        // }

        void addMenu(Menu menu){
            menus.emplace_back(menu);
        }

        void addAction(Option const& o) {
            this->options[o.optionName] = o;
        }

        void moveMenu(Menu& currMenu){
            currMenu = currMenu.menus.at(0);
        }

        Menu* getPrevMenu(){
            return prevMenu;
        }

        // //display all menus
        // void displayAllMenus(){
        //     std::cout << "Current Menu: " << menuName << std::endl;
        //     for (const auto &m : menus){
        //         std::cout << "Sub Menu: " << m->menuName << std::endl;
        //     }
        // }

        // Menu* subMenu(Menu* currMenu){
        //     currMenu = menus.at(0);
        //     return currMenu;
        // }
        std::vector<Menu> menus;
        std::map<std::string, Option> options;
    private:

        Menu* prevMenu = this;
        std::string menuName;
        std::string description;


        
};



#endif