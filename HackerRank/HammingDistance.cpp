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

static const uint64_t mostRightBit = (1ull << (sizeof(uint64_t) * 8 - 1));
static const int bitRate = sizeof(uint64_t) * 8;

class BitSet {
    class Iterator {
    public:
        Iterator() : mSize(0) {}
        Iterator(int size) 
        : mBitIndex(mostRightBit)
        , mArrayIndex(0)
        , mSize(size) {
            mEndArrayIndex = mSize / bitRate;
            if(mSize % bitRate) {
                ++mEndArrayIndex;
            }
            // 0  ==> 1
            // 1  ==> 63
            // 2  ==> 62
            // ...
            // 63 ==> 1
            // (64 - x)
            int yy = mSize % bitRate;
            if(yy == 0) {
                mEndBitIndex = 1ul;
            } else {
                mEndBitIndex = 1ul << bitRate - yy;
            }
        }

        Iterator& operator++() {
            mBitIndex >>= 1;
            if(!mBitIndex) {
                mBitIndex = mostRightBit;
                ++mArrayIndex;
            }
            return *this;
        }

        Iterator& operator--() {
            mBitIndex <<= 1;
            if(!mBitIndex) {
                mBitIndex = 1;
                --mArrayIndex;
            }
            return *this;
        }
        
        uint64_t bitIndex() const { return mBitIndex;}
        int arrayIndex() const { return mArrayIndex; }
        
        bool operator==(const Iterator& it) {
            return mBitIndex == it.mBitIndex && mArrayIndex == it.mArrayIndex;
        }

        bool end() {
            return mArrayIndex == mEndArrayIndex && mBitIndex == mEndBitIndex;
        }
        
        void begin(int index) {
            mArrayIndex = index / bitRate;
            if(index % bitRate) {
                ++mArrayIndex;
            }
            // 0  ==> 1
            // 1  ==> 63
            // 2  ==> 62
            // ...
            // 63 ==> 1
            // (64 - x)
            int yy = index % bitRate;
            if(yy == 0) {
                mBitIndex = 1ul;
            } else {
                mBitIndex = 1ul << bitRate - yy;
            }
        }

    private:
        uint64_t  mBitIndex;
        int       mArrayIndex;
        const int mSize;
        int       mEndArrayIndex;
        uint64_t  mEndBitIndex;
    };
    
public:
    BitSet(int size) {
        mArraySize = size / bitRate;
        if(size % bitRate) {
            ++mArraySize;
        }
        mSize = size;
        mArray = new uint64_t[mArraySize];
        beginFilling();
    }
    
    ~BitSet() {
        delete [] mArray;
    }
    bool bit(const Iterator& it) const { return (mArray[it.arrayIndex()] & it.bitIndex());}
    
    void executeC(int l1, int r1, char ch) {
        //memset((void*)(S + l1 - 1), ch - 'a', r1 - l1 + 1);
        Iterator it;
        it.begin(l1 - 1);
        
        if(ch - 'a' == 0)
            memset((void*)(&mArray[it.arrayIndex()]), 0, (r1 - l1 + 1)/8);
        else
            memset((void*)(&mArray[it.arrayIndex()]), 0xff, (r1 - l1 + 1)/8);
        // TODO
    }
    
    void executeS(int l1, int r1, int l2, int r2) {
    }
    
    void executeR(int l1, int r1) {
        Iterator it1;
        Iterator it2;
        it1.begin(l1 - 1);
        it2.begin(r1 - 1);
        int pos1 = l1 - 1;
        int pos2 = r1 - 1;
        for(;pos1 < pos2; ++it1, --it2, ++pos1, --pos2) {
            bool b1 = (mArray[it1.arrayIndex()] & it1.bitIndex());
            bool b2 = (mArray[it2.arrayIndex()] & it2.bitIndex());
            
            if(b1) {
                mArray[it2.arrayIndex()] |= it2.bitIndex();
            } else {
                mArray[it2.arrayIndex()] &= ~it2.bitIndex();
            }
            
            if(b2) {
                mArray[it1.arrayIndex()] |= it1.bitIndex();
            } else {
                mArray[it1.arrayIndex()] &= ~it1.bitIndex();
            }
        }
    }
    
    void executeW(int l1, int r1) {
        char* temp = new char[r1-l1 + 1];
        temp[r1-l1] = 0;
        Iterator it(r1);
        int pos = 0;
        for(it.begin(l1 - 1); !it.end(); ++it) {
            temp[pos++] = 'a' + bit(it);
        }
        if(pos != r1-l1 + 1) {
            cerr << "Something went wrong!!" << endl;
        }
        cout << temp;
        cout << endl;
        delete [] temp;
    }
    
    int executeH(int l1, int l2, int length) {
        Iterator it1(l1 + length - 1);
        Iterator it2(l2 + length - 1);
        it1.begin(l1 - 1);
        it2.begin(l2 - 1);
        int difference = 0;
        for(; !it1.end(); ++it1, ++it2) {
            difference += (bit(it1) != bit(it2));
        }
        return difference;
    }
    
    void beginFilling() {
        mBitIndex = mostRightBit;
        mArrayIndex = 0;
    }
    
    BitSet& operator<<(char bit) {
        if(bit) {
            mArray[mArrayIndex] |= mBitIndex;
        } else {
            mArray[mArrayIndex] &= ~mBitIndex;
        }
        mBitIndex >>= 1;
        if(!mBitIndex) {
            mBitIndex = mostRightBit;
            ++mArrayIndex;
        }
    }
    
    void testValues(const char* S) {
        uint64_t bitIndex = mostRightBit;
        int arrayIndex = 0;
        for(int i = 0; i < mSize; ++i) {
            if((bool)S[i] != (bool)(mArray[arrayIndex] & bitIndex)) {
                cerr << "BitSet error\n";
                exit(0);
            }
            bitIndex >>= 1;
            if(!bitIndex) {
                bitIndex = mostRightBit;
                ++arrayIndex;
            }
        }
    }
private:
    uint64_t* mArray;
    int mSize;
    int mArraySize;
    uint64_t mBitIndex;
    int mArrayIndex;
};

istream& operator>>(istream& in, BitSet& bitSet) {
    char ch;
    cin >> ch;
    bitSet << (ch - 'a');
    return in;
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
    static char temp[50001];
/*
    const char* p = S;
    for(int i = 0, j = 0; i < N;) {
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
                if(i >= max(r1, r2)) {
                    memcpy(&temp[j], &p[i], N - i);
                    break;
                } else {
                    temp[j++] = p[i++];
                }
            }
        }
    }
*/
    //cerr << l1 << ";" << r1 << ";" << l2 << ";" << r2 << "\n";
    --l1, --l2, --r1, --r2;
    // 0....l1....r1....l2....r2...N
    memcpy(temp, S, l1); // 0 - l1 ==> 0
    memcpy(temp + l1, S + l2, r2 - l2 + 1); // l2 - r2 ==> l1
    memcpy(temp + l1 + r2 - l2 + 1, S + r1 + 1, l2 - r1 -1); // r1 - l2 ==> l1 + l2 - r2 + 1
    memcpy(temp + l1 + r2 - l2 + 1 + l2 - r1 - 1, S + l1, r1 - l1 + 1); // l2 - r2 ==> l2
    memcpy(temp + l1 + r2 - l2 + 1 + l2 - r1 - 1 + r1 - l1 + 1, S + r2 + 1, N - r2 - 1); // l2 - r2 ==> l2
    memcpy((void*)S, temp, N);
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
    static char temp[50001];
    char* t = temp;
    for(char* p = (char*)S + (l1 - 1); p < S + r1; ++p, ++t) {
        *t = *p + 'a';
    }
    *t = 0;
    cout << temp << endl;
}

inline int popcount(uint64_t v) { 
/*
    v = (v & 0x1) 
        + ((v & 0x100) >> 8) 
        + ((v & 0x10000) >> 16) 
        + ((v & 0x1000000) >> 24)
        + ((v & 0x100000000) >> 32)
        + ((v & 0x10000000000) >> 40)
        + ((v & 0x1000000000000) >> 48)
        + ((v & 0x100000000000000) >> 56);
*/
    return (v & 0x1) 
        + ((v >> 8)  & 0x1)
        + ((v >> 16) & 0x1)
        + ((v >> 24) & 0x1)
        + ((v >> 32) & 0x1)
        + ((v >> 40) & 0x1)
        + ((v >> 48) & 0x1)
        + ((v >> 56) & 0x1);
    //if(v > sizeof(v)) {
    //    cerr << "something wrog " << v << "\n";
    //    cerr << sizeof(v) << " " << sizeof(uint64_t) << endl;
    //    exit(0);
    //}
}

int executeH2(const char* S, int l1, int l2, int length);
void executeH(const char* S, int l1, int l2, int length) {
    int distance = 0;
    const int origLength = length;
    const uint64_t* p1 = (const uint64_t*)(S + l1 - 1 ),
                  * p2 = (const uint64_t*)(S + l2 - 1);
    uint64_t r;
    char* p3 = (char*)&r;
    while(length >= sizeof(uint64_t)) {
        //distance += popcount((*p1++) ^ (*p2++)),
        r =(*p1++) ^ (*p2++);
        distance += p3[0] + p3[1] + p3[2] + p3[3] + p3[4] + p3[5] + p3[6] + p3[7];
        length -= sizeof(uint64_t);
    }
    distance += executeH2(S + origLength - length, l1, l2, length);
    cout << distance << endl;
}

int executeH2(const char* S, int l1, int l2, int length) {
    int distance = 0;
    const char* p1 = S + l1 - 1 + length - 1,
              * p2 = S + l2 - 1 + length - 1;
    while(length > 0) {
        distance += (*p1-- != *p2--),
        --length;
    }
    //cout << distance << endl;
    return distance;
}

void executeQueries_char(const char* S, int N) {
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

void executeQueries(BitSet& bitSet) {
    int l1, r1, l2, r2, length;
    char ch;
    cin >> ch;
    st.start("time");
    switch(ch) {
        case 'C': cin >> l1 >>  r1 >> ch; //cerr << l1 << " " << r1 << " " << ch << endl;
        //sscanf(pc, "%d %d %c", &l1, &r1, &ch);
        //scf >> l1 >>  r1 >> ch;
        //Print("C1:", S, N);
        bitSet.executeC(l1, r1, ch);
        st.saveDuration("time", "C");
        //Print("C2:", S, N);
        break;
        case 'S': cin >> l1 >>  r1 >> l2 >> r2; //cerr << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
        //sscanf(pc, "%d %d %d %d", &l1, &r1, &l2, &r2);
        //scf >> l1 >>  r1 >> l2 >> r2;
        bitSet.executeS(l1, r1, l2, r2);
        st.saveDuration("time", "S");
        //Print("S:", S, N);
        break;
        case 'R': cin >> l1 >>  r1; // cerr << l1 << " " << r1 << endl;
        //sscanf(pc, "%d %d", &l1, &r1);
        //scf  >> l1 >>  r1;
        bitSet.executeR(l1, r1);
        st.saveDuration("time", "R");
        //Print("R:", S, N);
        break;
        case 'W': cin >> l1 >>  r1; // cerr << l1 << " " << r1 << endl;
        //sscanf(pc, "%d %d", &l1, &r1);
        //scf >> l1 >> r1;
        bitSet.executeW(l1, r1);
        st.saveDuration("time", "W");
        break;
        case 'H': cin >> l1 >>  l2 >> length; // cerr << l1 << " " << l2 << " " << length << endl;
        //sscanf(pc, "%d %d %d", &l1, &l2, &length);
        //scf >> l1 >>  l2 >> length;
        bitSet.executeH(l1, l2, length);
        st.saveDuration("time", "H");
        break;
    }
}

int main(int argc, char* argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, M; // length of the string, number of queries
    st.start("read queries");
    cin >> N;
    string temp;

    if(argc <= 1) {
        BitSet bitSet(N);
        for(int i = 0; i < N; ++i) {
            cin >> bitSet;
        }
        //bitSet.testValues(S);
        cin >> M;
        getline(cin, temp);
        for(int i = 0; i < M; ++i) {
            executeQueries(bitSet);
        }
    } else {
        char ch;
        char* S = new char[N];
        for(int i = 0; i < N; ++i) {
            cin >> ch;
            S[i] = (ch == 'b');
        }
        cin >> M;
        getline(cin, temp);
        for(int i = 0; i < M; ++i) {
            executeQueries_char(S, N);
        }
        delete [] S;
    }

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
