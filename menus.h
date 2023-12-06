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

   Option(std::string optionName = "", std::string optionDescription = "", std::function<void(std::string)> func = std::function<void(std::string)>([](std::string s = "") {}))
        : optionName(optionName), optionDescription(optionDescription), func(func) {}

};

//base Menu class
class Menu {
    public:
        Menu (std::string menuName = "Main Menu", std::string description = "Main Menu", Menu* prevMenu = nullptr) : menuName(menuName), description(description), prevMenu(prevMenu){}

        virtual void displayMenu() const {
            std::cout << "Current menu: " << menuName << "\n";
            std::cout << "'" << description << "'" << std::endl;
        }

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

        std::vector<Menu> menus;
        std::map<std::string, Option> options;
    private:

        Menu* prevMenu = this;
        std::string menuName;
        std::string description;
};



#endif