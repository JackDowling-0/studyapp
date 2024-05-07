#ifndef PARSER_H
#define PARSER_H

#include <string>

class Parser {
    public:
        explicit Parser();
        bool isLetter(char letter);
        std::string trim(const std::string& str);

    private:
        std::string currLine;
};

#endif