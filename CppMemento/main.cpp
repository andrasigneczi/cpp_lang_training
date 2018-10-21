#include <thread>
#include "CppMemento.h"
#include <iostream>

/*
Leírás
------
- 2 szint: kategóriák és témák vagy feladatok
- inicializálás: minden témát egyenként megkeverni, és minden pozícióba egy-egy téma helyezése
minden kategóriából
- minden futtatáskor kérhetem az aktuális elemeket, vagy ugorhatok egyel előre/hátra a listában
- kérhetem az elemek újrarendezését
- ha egy kategóriában a végére érek, az elemek legyenek újra megkeverve

-n következő topik választása és kiírása
-p előző topik választása és kiírása
-s topikok megkeverése
-k kidolgozás kiírása
-h help
paraméter nélkül: aktuális topikok kiírása
*/

int main(int argc, char* argv[]) {
    if(argc == 1) {
        CppMemento m;
        m.load("questionlist_copy.txt");
        std::cout << m.getStringsAtCursor() << "\n";
    } else {
        for(int i = 0; i < argc; ++i) {
            if(std::string(argv[i]).compare("-n") == 0) {
                CppMemento m;
                m.load("questionlist_copy.txt");
                m.incCursor();
                m.save("questionlist_copy.txt");
                std::cout << m.getStringsAtCursor() << "\n";
            } else if(std::string(argv[i]).compare("-p") == 0) {
                CppMemento m;
                m.load("questionlist_copy.txt");
                m.decCursor();
                m.save("questionlist_copy.txt");
                std::cout << m.getStringsAtCursor() << "\n";
            } else if(std::string(argv[i]).compare("-s") == 0) {
                CppMemento m;
                m.load("questionlist.txt");
                m.shuffleByGroup();
                m.save("questionlist_copy.txt");
                std::cout << m.getStringsAtCursor() << "\n";
            } else if(std::string(argv[i]).compare("-k") == 0) {
                std::cout << "to be continued...\n";
            } else if(std::string(argv[i]).compare("-h") == 0) {
                std::cout << "cppmemento [-n] [-p] [-s] [-k] [-h]\n";
                std::cout << "\tdisplay recent topics\n";
                std::cout << "\t-n display next topics\n";
                std::cout << "\t-p display previous topics\n";
                std::cout << "\t-s shuffle topicss\n";
                std::cout << "\t-k display answers\n";
                std::cout << "\t-h dipslay help\n";
            }
        }
    }
    return 0;
}
