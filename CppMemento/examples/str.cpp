#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

// removing the leading zeros
void printHexStr(const string& x) {
    bool leadingZero = true;
    auto lz = [&leadingZero](char c) {
      if(c != '0' && leadingZero) {
          leadingZero = false;
      }
      if(c == '0' && leadingZero)
          return false;
      return true;
    };
    copy_if(x.begin(), x.end(), std::ostream_iterator<char>(std::cout, ""), lz);
    cout << endl;
}

//assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    size_t i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main() {
    string a("007bcd");
    printHexStr(a);
}