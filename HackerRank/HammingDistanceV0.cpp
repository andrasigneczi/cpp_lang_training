#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <chrono>
#include <unordered_map>
#include <iomanip>
#include <string.h>
#include "Util.h"

using namespace std;

class MyScanf {
public:
    MyScanf(const char* pc) : mPc(pc) {
        
    }
    
    MyScanf& operator>>(int& x) {
        x = 0;
        while(*mPc != 0 && (*mPc == ' ' || *mPc == '\t' || *mPc == '\n' || *mPc == '\a')) { ++mPc; }
        if(*mPc == 0) return *this;
        while(*mPc != 0 && (*mPc >= '0' && *mPc <= '9')) { 
            x *= 10;
            x += *mPc - '0';
            ++mPc; 
        }
        return *this;
    }

    MyScanf& operator>>(char& x) {
        x = 0;
        if(*mPc == 0) return *this;
        x = *mPc++;
        return *this;
    }
    
private:
    const char* mPc;
};


//assumes little endian
template<class T>
void printBits(T ptr)
{
    int size = sizeof(T);
    unsigned char *b = (unsigned char*) &ptr;
    unsigned char byte;
    int i, j;

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

void Print(const char* prefix, const char*S, int N) {
    cerr << prefix;
    for(size_t i = 0; i < N; ++i) {
        cerr << (S[i]?'b':'a');
    }
    cerr << endl;
}

// C l r ch: string becomes ch from l to r
// S l1 r1 l2 r2: swap two consecutive fragments
// R l r: reverse
// W l r: write out
// H l1 l2 length: Hamming distance between the consecutive substrings

void executeC(const char* S, int l1, int r1, char ch) {
    memset((void*)(S + l1 - 1), ch - 'a', r1 - l1 + 1);
    //cerr << "C params: " << l1 << " " << r1 << " " << ch << " " << S[l1 - 1] << endl;
}

void executeS(const char* S, int N, int l1, int r1, int l2, int r2) {
    static char* temp = new char[N];
    const char* p = S;
    int j = 0;
    for(int i = 0; i < N;) {
        if(i == l1 - 1) {
            memcpy(&temp[j], &p[l2 - 1], r2 - l2 + 1);
            i = r1;
            j += r2 - l2 + 1;
        } else if(i == l2 - 1) {
            memcpy(&temp[j], &p[l1 - 1], r1 - l1 + 1);
            i = r2;
            j += r1 - l1 + 1;
        } else {
            int end = min(l1 - 1, l2 - 1);
            if(i < end) {
                memcpy(&temp[j], &p[i], end - i);
                j += end - i;
                i = end;
            } else {
                int beg = max(r1, r2);
                if(i >= beg) {
                    memcpy(&temp[j], &p[i], N - i);
                    break;
                } else {
                    temp[j++] = p[i++];
                }
            }
        }
    }
    memcpy((void*)S, temp, N);
    //delete [] temp;
}

void executeR(const char* S, int l1, int r1) {
    //reverse(S.begin() + l1 - 1, S.begin() + r1);
    char* p1 = (char*)S + l1 - 1;
    char* p2 = (char*)S + r1 - 1;

    while(p1 < p2) {
        swap(*p1,*p2);
        ++p1;
        --p2;
    }
}

void executeW(const char* S, int l1, int r1) {
    //copy(S.begin() + (l1 - 1), S.begin() + r1, ostream_iterator<char>(cout, ""));
    //for_each(S.begin() + (l1 - 1), S.begin() + r1, [](const char x){ cout << (x?'b':'a');});
    for(char* p = (char*)S + (l1 - 1); p < S + r1; ++p) {
        cout << (char)(*p + 'a');
    }
    cout << endl;
}

static uint64_t popcount(uint64_t v) { 
    v = (v & 0x1) 
        + (!!(v & 0x100)) 
        + (!!(v & 0x10000)) 
        + (!!(v & 0x1000000))
        + (!!(v & 0x100000000))
        + (!!(v & 0x10000000000))
        + (!!(v & 0x1000000000000))
        + (!!(v & 0x100000000000000));
    //if(v > sizeof(v)) {
    //    cerr << "something wrog " << v << "\n";
    //    cerr << sizeof(v) << " " << sizeof(uint64_t) << endl;
    //    exit(0);
    //}
    return v; 
}

int executeH2(const char* S, int l1, int l2, int length);
void executeH(const char* S, int l1, int l2, int length) {
    int distance = 0;
    const int origLength = length;
    const uint64_t* p1 = (const uint64_t*)(S + l1 - 1 ),
    * p2 = (const uint64_t*)(S + l2 - 1);
    while(length >= sizeof(uint64_t)) {
        distance += popcount((*p1) ^ (*p2)),
        length -= sizeof(uint64_t),
        ++p1,
        ++p2;
    }
    distance += executeH2(S + origLength - length, l1, l2, length);
    cout << distance << endl;
}

int executeH2(const char* S, int l1, int l2, int length) {
    int distance = 0;
    const char* p1 = S + l1 - 1 + length - 1,
              * p2 = S + l2 - 1 + length - 1;
    while(length > 0) {
        distance += (*p1 != *p2),
        --length, 
        --p1,
        --p2;
    }
    //cout << distance << endl;
    return distance;
}

void executeQueries(const char* S, int N) {
    int l1, r1, l2, r2, length;
    char ch;
    cin >> ch;
    st.start("time");
    switch(ch) {
        case 'C': cin >> l1 >>  r1 >> ch; //cerr << l1 << " " << r1 << " " << ch << endl;
        //sscanf(pc, "%d %d %c", &l1, &r1, &ch);
        //scf >> l1 >>  r1 >> ch;
        //Print("C1:", S, N);
        executeC(S, l1, r1, ch);
        st.saveDuration("time", "C");
        //Print("C2:", S, N);
        break;
        case 'S': cin >> l1 >>  r1 >> l2 >> r2; //cerr << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
        //sscanf(pc, "%d %d %d %d", &l1, &r1, &l2, &r2);
        //scf >> l1 >>  r1 >> l2 >> r2;
        executeS(S, N, l1, r1, l2, r2);
        st.saveDuration("time", "S");
        //Print("S:", S, N);
        break;
        case 'R': cin >> l1 >>  r1; // cerr << l1 << " " << r1 << endl;
        //sscanf(pc, "%d %d", &l1, &r1);
        //scf  >> l1 >>  r1;
        executeR(S, l1, r1);
        st.saveDuration("time", "R");
        //Print("R:", S, N);
        break;
        case 'W': cin >> l1 >>  r1; // cerr << l1 << " " << r1 << endl;
        //sscanf(pc, "%d %d", &l1, &r1);
        //scf >> l1 >> r1;
        executeW(S, l1, r1);
        st.saveDuration("time", "W");
        break;
        case 'H': cin >> l1 >>  l2 >> length; // cerr << l1 << " " << l2 << " " << length << endl;
        //sscanf(pc, "%d %d %d", &l1, &l2, &length);
        //scf >> l1 >>  l2 >> length;
        executeH(S, l1, l2, length);
        st.saveDuration("time", "H");
        break;
    }
}

int main() {

    //printBits((uint64_t)0x5555555555555555ull);
    //printBits((uint64_t)0x3333333333333333ull);
    //printBits((uint64_t)0x0F0F0F0F0F0F0F0Full);
    //printBits((uint64_t)0x00FF00FF00FF00FFull);
    //printBits((uint64_t)0x0000FFFF0000FFFFull);
    //printBits((uint64_t)0x00000000FFFFFFFFull);
    //return 0;
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, M; // length of the string, number of queries
    st.start("read queries");
    cin >> N;
    string temp;

    char ch;
    //string S(N,0);
    char* S = new char[N];
    for(int i = 0; i < N; ++i) {
        cin >> ch;
        S[i] = (ch == 'b');
    }
    
    //string S;
    //cin >> S;
    
    cin >> M;
    getline(cin, temp);
    for(int i = 0; i < M; ++i) {
        executeQueries(S, N);
    }
    delete [] S;
    cerr << "clockC: " << setw(15) << group(st.duration("C")) << endl;
    cerr << "clockS: " << setw(15) << group(st.duration("S")) << endl;
    cerr << "clockR: " << setw(15) << group(st.duration("R")) << endl;
    cerr << "clockW: " << setw(15) << group(st.duration("W")) << endl;
    cerr << "clockH: " << setw(15) << group(st.duration("H")) << endl;
    cerr << string(22, '-') << endl;
    cerr << "sum:          " << group(st.duration("C") + st.duration("S") + st.duration("R") + st.duration("W") + st.duration("H")) << endl;
    cerr << "read queries: " << group(st.timeMs("read queries")) << endl;
    return 0;
}
