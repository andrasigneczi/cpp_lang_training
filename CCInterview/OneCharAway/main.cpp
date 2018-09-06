#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

bool ReplaceTest(std::string str1, std::string str2) {
    int differenceCount = 0;
    for(size_t i = 0; i < str1.length(); ++i) {
        if(str1[i] != str2[i]){
            ++differenceCount;
            if(differenceCount>1)
                return false;
        }
    }
    return true;
}

bool InsertTest(std::string str1, std::string str2) {
    size_t i = 0;
    size_t j = 0;
    int differenceCount = 0;
    while(i < str1.length() && j < str2.length()) {
        if(str1[i] != str2[j]) {
            ++differenceCount;
            if(differenceCount>1)
                return false;
            if(str1.length() > str2.length()) {
                ++i;
            } else {
                ++j;
            }
            continue;
        }
        ++i;
        ++j;
    }
    return true;
}

bool Test(std::string str1, std::string str2) {
    if(str1.length() == str2.length())
        return ReplaceTest(str1, str2);
    if(abs(str1.length()-str2.length()) == 1 )
        return InsertTest(str1, str2);
    return false;
}

int main(int argc, char* argv[]) {
    
    std::cout << "pale, ple:    " << Test("pale", "ple"   ) << "(expected: 1)\n";
    std::cout << "pales, pale:  " << Test("pales", "pale" ) << "(expected: 1)\n";
    std::cout << "pale, bale:   " << Test("pale", "bale"  ) << "(expected: 1)\n";
    std::cout << "pale, bake:   " << Test("pale", "bake"  ) << "(expected: 0)\n";
    std::cout << "pale, paleee: " << Test("pale", "paleee") << "(expected: 0)\n";
    std::cout << "pale, pale:   " << Test("pale", "pale"  ) << "(expected: 1)\n";
    return 0;
}