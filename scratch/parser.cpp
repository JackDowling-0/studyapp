#include "head/parser.h"

Parser::Parser(){};

bool Parser::isLetter(char letter) {
    return (letter >= 'A' && letter <= 'Z' || letter >= 'a' && letter <= 'z');
}

std::string Parser::trim(const std::string& str) {
    return str;
}