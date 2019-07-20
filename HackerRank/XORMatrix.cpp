#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

using ull = unsigned long long;

struct Compare {
    
};

/*
 * Complete the xorMatrix function below.
 */
vector<ull> xorMatrix_(ull m, vector<ull> first_row) {
    map<vector<ull>,ull> cache;
    vector<ull> nextRow(first_row.size());
    cache.emplace(first_row, 0);
    bool cacheIsReady = false;
    for(ull j = 1; j < m; ++j) {
        for(ull i = 0; i < first_row.size(); ++i) {
            //nextRow.push_back(first_row[i] ^ first_row[(i + 1)%first_row.size()]);
            nextRow[i] = first_row[i] ^ first_row[(i + 1)%first_row.size()];
        }
        
        if(!cacheIsReady) {
            auto it = cache.find(nextRow);
            if(it != cache.end()) {
                cout << "First occurance: " << it->second << "th row\n";
                cout << "Repeat after " << j << "th row\n";
                cout << "m: " << m << " rows\n";
                ull M = (((ull)m - 1 - it->second) % (j - it->second)) + it->second;
                cout << m << "th row will be:\n";
                for(auto itM = cache.begin(); itM != cache.end(); ++itM) {
                    if(itM->second == M) {
                        copy(itM->first.begin(), itM->first.end(), ostream_iterator<int>(cout, " "));
                        cout << "\n";
                        break;
                        //return itM->first;
                    }
                }
                cacheIsReady = true;
            } else {
                cache.emplace(nextRow, j);
            }
        }
        if(j%100000 == 0)
            cout << j << "th row\n";
        first_row = nextRow;
    }
    return first_row;
}

vector<ull> iterate(ull m, vector<ull> first_row) {
    vector<ull> nextRow(first_row.size());
    for(ull j = 1; j < m; ++j) {
        for(ull i = 0; i < first_row.size(); ++i) {
            nextRow[i] = first_row[i] ^ first_row[(i + 1)%first_row.size()];
        }
        first_row = nextRow;
    }
    return first_row;
}

// After 2^x round, result will be A[i]^A[(i+2^x)%n]
// For n x m matrix for every (m-1) = {power of 2} a[i,j + m-1] = a[i, j] ^ a[(i + m - 1) % n, j]
vector<ull> xorMatrix(ull m, vector<ull> first_row) {
    auto ttt = iterate(m, first_row);
    copy(ttt.begin(), ttt.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";
    
    ull o = 1;
    --m;
    vector<ull> nextRow(first_row.size());
    while(o != 0) {
        if((m&o) != 0) {
            cout << o << "\n";
            for(size_t i = 0; i < first_row.size(); ++i) {
                nextRow[i] = first_row[i]^first_row[(i + o)%first_row.size()];
            }
            first_row = nextRow;
        }
        o <<= 1;
    }
    return first_row;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    ull n = stoull(nm[0]);

    ull m = stoull(nm[1]);

    string first_row_temp_temp;
    getline(cin, first_row_temp_temp);

    vector<string> first_row_temp = split_string(first_row_temp_temp);

    vector<ull> first_row(n);

    for (int first_row_itr = 0; first_row_itr < n; first_row_itr++) {
        int first_row_item = stoi(first_row_temp[first_row_itr]);

        first_row[first_row_itr] = first_row_item;
    }

    vector<ull> last_row = xorMatrix(m, first_row);

    for (int result_itr = 0; result_itr < last_row.size(); result_itr++) {
        fout << last_row[result_itr];

        if (result_itr != last_row.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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
