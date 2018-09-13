#include "LinkedList.h"

void printItems(LinkedList& ll) {
    for(size_t i = 0; i < ll.size(); ++i) {
        std::cout << i << ": " << ll[i];
        if( i != ll.size() - 1)
            std::cout << ";  ";
    }
    std::cout << std::endl;
}

void Test() {
    LinkedList ll;
    ll.add(0);
    ll.add(1);
    ll.add(2);
    ll.add(3);
    ll.add(4);
    
    printItems(ll);

    std::cout << "replace 3. item\n";
    ll.replace(3, 300);
    printItems(ll);

    std::cout << "removing 2. item\n";
    ll.remove(2);
    printItems(ll);

    std::cout << "removing 1. item\n";
    ll.remove(1);
    printItems(ll);

    std::cout << "removing 0. item\n";
    ll.remove(0);
    printItems(ll);

    std::cout << "replace 0. item\n";
    ll.replace(0, 100);
    printItems(ll);

    std::cout << "replace 1. item\n";
    ll.replace(1, 200);
    printItems(ll);

    std::cout << "insert into 0. position\n";
    ll.insert(0, 0);
    printItems(ll);

    std::cout << "insert into 1. position\n";
    ll.insert(1, 33);
    printItems(ll);

    std::cout << "insert into 2. position\n";
    ll.insert(2, 99);
    printItems(ll);

    std::cout << "insert into 4. position\n";
    ll.insert(4, 199);
    printItems(ll);

    std::cout << "insert into 6. position\n";
    ll.insert(6, 299);
    printItems(ll);
}

void PartialTest() {
    LinkedList ll;
    ll << 3 << 5 << 8 << 5 << 10 << 2 << 1;
    printItems(ll);
    ll.partition(5);
    ll.partition(5);
    printItems(ll);
}

// Number A and Number B represented in a linked list. The digits are stored reversed order.
void SumListV1Test() {
    LinkedList A, B, C;
    A << 7 << 1 << 6; // 617
    B << 5 << 9 << 2 << 1; // 1295
    // A + B = ?
    size_t i = 0;
    int rem = 0;
    
    while( i < A.size() && i < B.size()) {
        C << ((A[i] + B[i] + rem) % 10);
        rem = (A[i] + B[i] + rem) / 10;
        ++i;
    }
    
    while( i < A.size()) {
        C << ((A[i] + rem) % 10);
        rem = (A[i] + rem) / 10;
        ++i;
    }

    while( i < B.size()) {
        C << ((B[i] + rem) % 10);
        rem = (B[i] + rem) / 10;
        ++i;
    }
    printItems(C);
}

// Number A and Number B represented in a linked list. The digits are stored forward order.
void SumListV2Test() {
    LinkedList A, B, C;
    A << 6 << 1 << 7; // 617
    B << 1 << 2 << 9 << 5; // 1295
    // A + B = ?
    size_t i = A.size() - 1;
    size_t j = B.size() - 1;
    int rem = 0;

    while(i >= 0 && j >= 0) {
        C << ((A[i] + B[j] + rem) % 10);
        rem = (A[i] + B[j] + rem) / 10;
        if(i == 0 || j == 0) break;
        --i;
        --j;
    }
    
    while(i > 0) {
        --i;
        C << ((A[i] + rem) % 10);
        rem = (A[i] + rem) / 10;
        if(i == 0) break;
    }

    while(j > 0) {
        --j;
        C << ((B[j] + rem) % 10);
        rem = (B[j] + rem) / 10;
        if(j == 0) break;
    }
    printItems(C);
}

int main(int argc, char* argv[]) {
    //Test();
    //PartialTest();
    SumListV1Test();
    SumListV2Test();
    return 0;
}
