#ifndef FLASHCARDS_H
#define FLASHCARDS_H



namespace Flash 
{

//public var for anything in the Flash namespace; tracks stack size
int nextID;


//flashcard container
class Flashcard {
    public:
        struct FlashcardInfo {
            FlashcardInfo(int ID = 0, std::string question = "", std::string answer = "") : ID(ID), question(question), answer(answer){};
            int ID;
            std::string question;
            std::string answer;
        };

        //default constructor for individual flashcard
        Flashcard(int id = -1, std::string q = "", std::string a = "") : ID(id), question(q), answer(a){}
        
        //destructor
        ~Flashcard(){}

        //Return a struct with flashcard attributes //hopefully this doesn't overcomplicate things
        FlashcardInfo getInfo() const {
            return {ID, question, answer};
        }

        //Update the attributes of the current flashcard
        void updateElement(std::string q = "", std::string a = "") {

            if (q != "" && q != "//leave//") {
                question = q;
            }

            if (a != "") {
                answer = a;
            }
        }

        void updateID(const int& num){
            ID = num;
        }

    private:
        int ID;
        std::string question;
        std::string answer;
};


//Manager for flashcards and flashcard related methods
class FlashcardManager
{

// Public attributes
public:
    std::map<int, Flashcard> flashcards;
    //init logic
    FlashcardManager(){
        //set up next ID
        nextID = flashcards.size();
    }


    //construct and add flashcards to the stack based on provided information
    void addFlashcard(int ID = nextID, std::string question = "", std::string answer = ""){
        flashcards.emplace(ID, Flashcard(ID, question, answer));
        nextID++;
    }

    //Flashcard overload
    void addFlashcard(const Flashcard& card){
        flashcards.emplace(nextID, card);
        nextID++;
    }

    //creates buffer library vector, pushes cards in based on IDs, then destroys and remakes existing library
    void updateIDs(){
        //We can use a vector because the cards will be in order anyway
        std::vector<Flashcard> bffr;
        nextID = 0;
        for (auto it : flashcards){
            it.second.updateID(nextID);
            bffr.push_back(it.second);
            nextID++;
        }
        flashcards.clear();
        for (auto it : bffr){
            flashcards.emplace(it.getInfo().ID, it);
        }
    }

    //display specified flashcard
    void displayCard(const int& cardNumber) {

        // std::cout << "Printing flashcard...\n";
        if (flashcards.find(cardNumber) != flashcards.end()) {
            Flashcard::FlashcardInfo info = flashcards[cardNumber].getInfo();
            
            std::cout << "Card ID: " << info.ID << "." << std::endl;
            std::cout << "Question: " << info.question << std::endl;
            std::cout << "Answer: " << info.answer << std::endl;

        } else {

            std::cout << "Error! Flashcard not found!" << std::endl;
            }
        }

    //display specified flashcard
    void displayCard(const Flashcard& card) {

            Flashcard::FlashcardInfo info = card.getInfo();
            
            std::cout << "Card ID: " << info.ID << "." << std::endl;
            std::cout << "Question: " << info.question << std::endl;
            std::cout << "Answer: " << info.answer << std::endl;

        }

    //display all flashcards currently on the stack
    void displayCards() {
        std::cout << "Printing flashcards...\n";

        if (flashcards.empty()){
            std::cout << "No flashcards found!";
            return;
        }

        for (const auto& card : flashcards) {
            //temporary info struct that will be deleted once it goes out of scope
            Flashcard::FlashcardInfo info = card.second.getInfo();
            std::cout << "Card ID: " << info.ID << "." << std::endl;
            std::cout << "Question: " << info.question << std::endl;
            std::cout << "Answer: " << info.answer << std::endl;
        }
    }

    //call destructor for given flashcard and revmove it from the map
    //TODO: Perform cleanup
    void destroyFlashcard(const int& cardNumber) {
        auto it = flashcards.find(cardNumber);
        if (it != flashcards.end()) {
            flashcards.erase(cardNumber);

        } else {
            std::cout << "Error! Card number out of bounds!" << std::endl;
        }
    }

    //manager-level update function to call flashcard, update its attributes and print card if requested
    void updateCard(const int& cardNumber, std::string newQuestion = "", std::string newAnswer = "", bool print = false){

        if (flashcards.find(cardNumber) != flashcards.end()){
            if (newQuestion != "" || newAnswer != ""){

                //create an iterator
                auto &card = flashcards.at(cardNumber);
                card.updateElement(newQuestion, newAnswer);

                if (print != false) {
                    displayCard(cardNumber);
                }
            }

        } else {

            std::cout << "Error! Flashcard not found!" << std::endl;
        }

    }
    void appendCardToStorage(Flashcard card){
        std::ofstream library("library.txt", std::ios_base::app);

        library << "ID: " << card.getInfo().ID << std::endl;
        library << "Question: " << card.getInfo().question << std::endl;
        library << "Answer: " << card.getInfo().answer << std::endl;
        
        library.close();
    }

    void writeLibraryToStorage(){
        std::vector<Flashcard> bffr;
        for (const auto& it : flashcards){
            bffr.push_back(it.second);
        }

        std::ofstream library("library.txt", std::ios::out);

        for (const auto& it : bffr){
            library << "ID: " << it.getInfo().ID << std::endl;
            library << "Question: " << it.getInfo().question << std::endl;
            library << "Answer: " << it.getInfo().answer << std::endl;
        }
        library.close();
    }

    void readFromStorage(){
        
        std::ifstream library("library.txt");
        std::ifstream dump("dump.txt");
        //first time setup
        if (!library || !dump){
            if (!dump){
                std::ofstream dump("dump.txt");
                dump.close();
            }
            std::ofstream library("library.txt");
            library.close();
            return;
        }

        int d;
        std::string q = "";
        std::string a = "";
        std::string line;
        int counter = 0;
        Flashcard card;
        while (std::getline(library, line)){
            if (counter == 0){
                d = stoi(line.substr(4));
                counter++;
                continue;
            } else if (counter == 1){
                q = line.substr(10);
                counter++;
                continue;
            } else if (counter == 2){
                a = line.substr(8);
                counter = 0;
                addFlashcard(nextID, q, a);
                continue;
            }
        }
        
        library.close();
    }

    const std::vector<Flashcard> convertCards(const std::map<int, Flashcard>& flashcards) {
        std::vector<Flashcard> vecBffr;
        for (const auto& it : flashcards){
            vecBffr.emplace_back(it.second.getInfo().ID, it.second.getInfo().question, it.second.getInfo().answer);
        }

        return vecBffr;
    }

    int practiceCard(int num){

        const auto& card = flashcards.at(num);

        std::cout << "(" << card.getInfo().ID << ") " << card.getInfo().question;
        char c = getch();
        if (c == 'q'){
            return(1);
        }
        fflush(stdin);

        std::cout << "\n      " << card.getInfo().answer << "\n";
        c = getch();
        if (c == 'q'){
            return(1);
        }
        fflush(stdin);

        return 0;
    }
};


//end of Flash namespace
}

#endif
