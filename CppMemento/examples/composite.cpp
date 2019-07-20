// My Drive >> Development >> Java >> Design Patterns
// structural pattern

#include <iostream>

class Sugar {
public:
    Sugar():spoons(0) {}
    void add(int spoonsOfSugar) { spoons += spoonsOfSugar; }
    int amount() const { return spoons; }
private:
    int spoons;
};

class Lemon {
public:
    Lemon():spoons(0) {}
    void add(int spoonsOfLemon) { spoons += spoonsOfLemon; }
    int amount() const { return spoons; }
private:
    int spoons;
};

class TeaBag {
public:
    TeaBag():bagNum(0) {}
    void add(int teaBagNum) { bagNum += teaBagNum; }
    int amount() const { return bagNum; }
private:
    int bagNum;
};


class CupOfTea {
public:
    void add(int spoonsOfSugar, int spoonsOfLemon, int teaBagNum) {
	sugar.add(spoonsOfSugar);
	lemon.add(spoonsOfLemon);
	teaBag.add(teaBagNum);
    }

    void printIngredients() {
	std::cout << "sugar: " << sugar.amount() << " spoon(s)\n";
	std::cout << "lemon: " << lemon.amount() << " spoon(s)\n";
	std::cout << "tea bags: " << teaBag.amount() << " bag(s)\n";
    }
private:
    Sugar sugar;
    Lemon lemon;
    TeaBag teaBag;
};

int main(int argc, char*argv[]) {
    CupOfTea tea;
    tea.add(2, 1, 3);
    tea.printIngredients();
    return 0;
}
