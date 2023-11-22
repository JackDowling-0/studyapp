#ifndef MENUS_H
#define MENUS_H

#include <map>
#include <functional>
//forward declaration
class Menu;

//make an addFunction function that takes in an identifier and a function
//make an execute function that takes in an an identifier and runs the function

//options class
class Options {
    public:
        Options(const std::string& optionName, Menu& nextMenu) : optionName(optionName), nextMenu(&nextMenu){}

        Menu* getPrevMenu() const {
            return prevMenu;
        }

        const std::string& GetOptionName() const {
            return optionName;
        }

    private:
        std::string optionName;
        Menu* nextMenu;
        Menu* prevMenu;

};
//subclasses
class Menu {
    public:
        Menu (const std::string& name) : name(name){}


        void addFunction(std::string functionName, std::function<void()> func) {
            functions[functionName] = func;
        }

        void executeFunction(const std::string& functionName) {
            if (functions.find(functionName) != functions.end()) {
                functions[functionName]();
            } else {
                std::cerr << "Function not found" << std::endl;
            }
        }

        void displayMenu() const {
            std::cout << "Current menu: " << name << std::endl;
            std::cout << "Options: " << std::endl;

            for (const auto& option : options) {
                std::cout << option.GetOptionName() << std::endl;
            }

        }

        void addOption(const std::string& optionName, Menu& nextMenu){
            options.emplace_back(optionName, nextMenu);
        }

    private:
        const std::string name;
        std::vector<Options> options;
        std::map<std::string, std::function<void()>> functions;
};


#endif