#ifndef __UTIL_H__
#define __UTIL_H__

using namespace std;

string group(size_t x) {
    stringstream ss;
    string s = to_string(x);
    int p = s.length() % 3;
    for(size_t i = 0; i < s.length(); ++i) {
        if(i % 3 == p) {
            ss << ' ';
        }
        ss << s[i];
    }
    return ss.str();
}

using namespace std::chrono;

class StopWatch {

public:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
    void start(string key) {
        auto t = high_resolution_clock::now();
        clocks.erase(key);
        clocks.emplace(key, t);
    }
    
    size_t timeMs(string key) {
        auto s = clocks.find(key);
        if(s != clocks.end()) {
            auto t = high_resolution_clock::now();
            return duration_cast<microseconds>(t - s->second).count();
        }
        return 0;
    }
    
    void saveDuration(string keyT, string keyD) {
        auto s = clocks.find(keyT);
        auto d = durations.find(keyD);
        
        if(s != clocks.end()) {
            auto t = high_resolution_clock::now();
            if(d != durations.end()) {
                d->second += duration_cast<microseconds>(t - s->second).count();
            } else {
                durations.emplace(keyD, duration_cast<microseconds>(t - s->second).count());
            }
        }
    }
    
    size_t duration(string key) {
        auto s = durations.find(key);
        if(s != durations.end()) {
            return s->second;
        }
        return 0;
    }
    
private:
    unordered_map<string, time_point> clocks;
    unordered_map<string, size_t>     durations;
};

StopWatch st;

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


#endif // __UTIL_H__