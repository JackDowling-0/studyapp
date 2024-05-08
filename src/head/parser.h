#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "flashcardmanager.h"

//attempt to create flashcards from every line in a file
std::vector<Flashcard> parseBulkFile(const std::string& fileName);

//helper function for parseLine
bool isLetter(char letter);

//get rid of whitespace (python does it better)
std::string trim(const std::string& str);

//parse through full line, returning a Flashcard object
Flashcard parseLine(const std::string& str, char separator);

//same as bulkfile, but don't return a vector
void parsefile(const std::string& fileName);

//opens the batch file, prompts user for input, writes library to memory and storage once the file is closed
void bulkUpload();

//prompt user for full line, save and write to storage
void startLineUpload();


#endif