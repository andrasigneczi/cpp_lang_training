#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
using ull = unsigned long long;

// Complete the arrayManipulation function below.
ull arrayManipulation1(int n, vector<vector<int>> queries) {
    vector<ull> arr(n);
    // cout << "queries: " << queries.size() << "\n";
    for(size_t i = 0; i < queries.size(); ++i) {
        for(size_t j = queries[i][0] - 1; j <= queries[i][1] - 1; ++j) {
            arr[j] += queries[i][2];
        }
    }
    ull retv = 0;
    for_each(arr.begin(), arr.end(), [&retv](const ull x) {if(retv < x) retv = x;});
    return retv;
}

struct Node {
    ull  mPoint;
    bool mStart; // this is a start or end point
    ull  mValue;
    ull  mId; // beg-end has the same unique id
    bool operator()(const Node& n1, const Node& n2) {
        if(n1.mPoint == n2.mPoint) {
            if(n1. mStart == n2.mStart) {
                return n1.mId < n2.mId;
            }
            return n1.mStart;
        }
        return n1.mPoint < n2.mPoint;
    }
};

// Interval handling
ull arrayManipulation(int n, vector<vector<int>>& queries) {
    vector<Node> arr(n);
    // cout << "queries: " << queries.size() << "\n";
    ull id = 0;
    for(size_t i = 0; i < queries.size(); ++i) {
        arr.push_back({(ull)queries[i][0], true, (ull)queries[i][2], id});
        arr.push_back({(ull)queries[i][1], false, (ull)queries[i][2], id++});
    }
    
    Node node;
    sort(arr.begin(), arr.end(), node);
    
    ull retv = 0;
    ull currVal = 0;
    for_each(arr.begin(), arr.end(), [&](const Node& x) {
        if(x.mStart) {
            currVal += x.mValue;
        } else {
            currVal -= x.mValue;
        }
        if(retv < currVal) retv = currVal;
        
    });
    return retv;
}

class Interval {
public:
    Interval() {}
    Interval(ull beg, ull end, ull val)
    : mBegin(beg)
    , mEnd(end)
    , mValue(val)
    {}
    
    bool operator()(const Interval& i1, const Interval& i2) const {
        return i1.mBegin < i2.mBegin;
    }

    bool operator<(const Interval& i) const {
        return mBegin < i.mBegin;
    }
    
    bool operator==(const Interval& i) const {
        return i.mBegin == mBegin;
    }

    void setValue(const ull val) const { mValue = val; }
    ull value() const { return mValue; }
    ull begin() const { return mBegin; }
    ull end() const { return mEnd; }
    bool valid() const { return mBegin <= mEnd; }
    
private:
    ull mBegin;
    ull mEnd;
    mutable ull mValue;
};

ostream& operator<<(ostream& o, const Interval& i) {
    o << "begin: " << i.begin() << " end: " << i.end() << " value: " << i.value();
    return o;
}

typedef set<Interval, Interval> ISet;
typedef set<Interval, Interval>::iterator ISetIt;

class IntervalSet {
public:
    void add(const Interval i) {
        if(!i.valid()) {
            return;
        }
        
        if(mIntervals.size() == 0) {
            emplace(i);
            return;
        }
        
        ISetIt it = mIntervals.lower_bound(i); // not less
        if(it == mIntervals.end()) { // 1, 2, 3, 4, 5, 6
            // all of them less than *it, examine the last one
            auto last = mIntervals.end();
            --last;
            if(!addToTheEnd(last, i)) {
                cerr << "Something wrong\n";
            }
        } else if(*it == i) { // 7, 8, 9, 10
            if(!intersect(it, i)) {
                cerr << "Something wrong\n";                
            }
        } else { // 11-18
            if(!intersect2(it, i)) {
                cerr << "Something wrong\n";                
            }
        }
    }
    
    void emplace(const Interval i) {
        if(i.valid()) {
            mIntervals.emplace(i);
        }
    }
    
    bool addToTheEnd(ISetIt last, const Interval i) {
        if(!i.valid()) return false;
        
        // cases: 1, 2, 3, 4, 5, 6, 7, 8
        if(last->begin() < i.begin()) { // 1, 2, 3, 4, 5, 6
        
            if(last->end() > i.begin()) { // 4, 5, 6
                if(last->end() < i.end()) { // 4
                    Interval interval1(i.begin(), last->end(), last->value() + i.value());
                    Interval interval2(last->end() + 1, i.end(), i.value());
                    Interval interval3(last->begin(), i.begin() - 1, last->value());
                    mIntervals.erase(last);
                    emplace(interval1);
                    emplace(interval3);
                    add(interval2);
                } else if(last->end() == i.end()) { // 5
                    Interval interval1(i.begin(), i.end(), last->value() + i.value());
                    Interval interval2(last->begin(), i.begin() - 1, last->value());
                    mIntervals.erase(last);
                    emplace(interval1);
                    emplace(interval2);
                } else if(last->end() > i.end()){ // 6
                    Interval interval1(i.begin(), i.end(), last->value() + i.value());
                    Interval interval2(i.end() + 1, last->end(), last->value());
                    Interval interval3(last->begin(), i.begin() - 1, last->value());
                    mIntervals.erase(last);
                    emplace(interval1);
                    emplace(interval3);
                    add(interval2);
                }
            } else if(last->end() == i.begin()) { // 3
                Interval interval1(i.begin(), i.begin(), last->value() + i.value());
                Interval interval2(i.begin() + 1, i.end(), i.value());
                Interval interval3(last->begin(), i.begin() - 1, last->value());
                mIntervals.erase(last);
                emplace(interval1);
                emplace(interval2);
                emplace(interval3);
            } else if(last->end() < i.begin()) { // 1, 2
                emplace(i);
            }
        } else {
            return false;
        }
        return true;
    }

    bool intersect(ISetIt it, const Interval i) {
        if(!i.valid()) return false;
        
        if(it->end() == i.end()) { // 9
            it->setValue(it->value() + i.value());
        } else { // 7, 8, 10
            if(it->end() < i.end()) { // 7, 8
                it->setValue(i.value() + it->value());
                Interval interval(it->end() + 1, i.end(), i.value());
                add(interval);
                
            } else { // 10
                Interval interval1(it->begin(), i.end(), it->value() + i.value());
                Interval interval2(i.end() + 1, it->end(), it->value());
                mIntervals.erase(it);
                emplace(interval1);
                emplace(interval2);
            }
        }
        return true;
    }
    
    // add will be called with the reminder
    bool intersect2(ISetIt it, const Interval i) {
        if(!i.valid()) return false;
        
        // *it > i
        // case: 11, 12, 13, 14, 15, 16, 17, 18
        if(it->begin() < i.end()) { // 11, 12, 13, 14
            if(it->end() < i.end()) { // 11, 12
                it->setValue(i.value() + it->value());
                Interval interval1(i.begin(), it->begin() - 1, i.value());
                Interval interval2(it->end() + 1, i.end(), i.value());
                add(interval1);
                add(interval2);
            } else if(it->end() == i.end()) { // 13
                it->setValue(i.value() + it->value());
                Interval interval(i.begin(), it->begin() - 1, i.value());
                add(interval);
            } else { // 14
                Interval interval1(i.begin(), it->begin() - 1, i.value());
                Interval interval2(it->begin(), i.end(), it->value() + i.value());
                Interval interval3(i.end() + 1, it->end(), it->value());
                mIntervals.erase(it);
                add(interval1);
                emplace(interval2);
                emplace(interval3);
            }
        } else if(it->begin() == i.end()) { // 15, 16
            if(it->end() == i.end()) { // 15
                Interval interval(i.begin(), it->begin() - 1, i.value());
                it->setValue(it->value() + i.value());
                add(interval);
            } else { // 16
                Interval interval1(i.begin(), i.end() - 1, i.value());
                Interval interval2(it->begin(), it->begin(), it->value() + i.value());
                Interval interval3(it->begin() + 1, it->end(), it->value());
                mIntervals.erase(it);
                add(interval1);
                emplace(interval2);
                emplace(interval3);
            }
        } else { // 17, 18
            if(it != mIntervals.begin()) {
                addToTheEnd(prev(it), i);
            } else {
                emplace(i);
            }
        }
        return true;
    }
    
    void printIntervals() {
        copy(mIntervals.begin(), mIntervals.end(), ostream_iterator<Interval>(cout, "\n"));
    }
    
    ull maxValue() const { 
        ull maxValue = 0;
        for_each(mIntervals.begin(), mIntervals.end(), [&](const Interval& i) {
           if(maxValue < i.value()) {
               maxValue = i.value();
           }
        });
        return maxValue;
    }

private:
    ISet mIntervals;
};

ull arrayManipulation2(int n, vector<vector<int>> queries) {
    IntervalSet intervalSet;
    for_each(queries.begin(), queries.end(), [&](const vector<int>& i){
        //copy(i.begin(), i.end(), ostream_iterator<int>(cout, " ")); cout << "\n";
        intervalSet.add(Interval{(ull)i[0], (ull)i[1], (ull)i[2]});
    });
    //intervalSet.printIntervals();
    return intervalSet.maxValue();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    std::random_device rd;
    std::mt19937 g(rd());

    //for(size_t i = 1; i <= queries.size(); ++i) {
        //for(int jj = 0; jj < 10; ++jj) {
            //vector<vector<int>> queries_cp;
            //copy(queries.begin(), queries.begin() + i, back_inserter(queries_cp));
            //shuffle(queries.begin(), queries.end(), g);
    
            using namespace std::chrono;
            auto t0 = high_resolution_clock::now();
            ull result1 = arrayManipulation1(n, queries);
            fout << result1 << "\n";
            auto t1 = high_resolution_clock::now();
            fout << duration_cast<milliseconds>(t1-t0).count() << " milliseconds passed\n";
            fout.flush();

            t0 = t1;
            ull result2 = arrayManipulation2(n, queries);
            fout << result2 << "\n";
            t1 = high_resolution_clock::now();
            fout << duration_cast<milliseconds>(t1-t0).count() << " milliseconds passed\n";
            fout.flush();

            t0 = t1;
            ull result3 = arrayManipulation(n, queries);
            fout << result3 << "\n";
            t1 = high_resolution_clock::now();
            fout << duration_cast<milliseconds>(t1-t0).count() << " milliseconds passed\n";
            fout.flush();
        //}
    //}

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
