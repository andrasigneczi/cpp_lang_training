#include <thread>
#include "CppMemento.h"

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

*/

int main(int argc, char* argv[]) {
    CppMemento m;
    m.Load();
    m.dumpStorage();
    return 0;
}