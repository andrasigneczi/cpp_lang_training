#include <string>
#include <iostream>

void permutation(std::string str, std::string prefix);
void permutation(std::string str) {
    permutation(str, "");
}

void permutation(std::string str, std::string prefix) {
    if(str.length()==0) {
        std::cout << prefix << std::endl;
    } else {
        for(size_t i = 0; i < str.length(); ++i) {
            std::string rem = str.substr(0,i) + str.substr(i+1);
            permutation(rem, prefix + str[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    permutation("0123");
}
