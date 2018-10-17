#include <bits/stdc++.h>

/*
Given an array with ints. Calculate the sum of every possible subset's xor of the array and return 
with Sum() % (pow(10,9) + 7)
*/

using namespace std;

vector<string> split_string(string);
using ull = unsigned long long;

ull traversalSum(const vector<int>& arr, vector<int>& groupMembers, size_t groupSize, size_t start = 0) {
    if(groupSize == 0) {
        // XOR the group members
        int xorV = 0;
        if(groupMembers.size() > 0) {
            for(size_t i = 0; i < groupMembers.size(); ++i) {
                xorV ^= groupMembers[i];
            }
        }
        // cout << "group:";
        // copy(groupMembers.begin(), groupMembers.end(), ostream_iterator<int>(cout, ","));
        // cout << "\n";
        return xorV;
    }
    
    ull retv = 0;
    if(groupSize == 1) {
        ull xorv = traversalSum(arr, groupMembers, 0);
        for(size_t i = start; i < arr.size(); ++i) {
            xorv ^= arr[i];
            retv += xorv;
            xorv ^= arr[i];
        }
        return retv;
    }

    for(size_t i = start; i < arr.size(); ++i) {
        groupMembers.push_back(arr[i]);
        retv += traversalSum(arr, groupMembers, groupSize - 1, i + 1);
        groupMembers.erase(groupMembers.end() - 1);
    }
    return retv;
}

ull xoringNinja_rec(vector<int> arr) {
    ull retV = 0;
    vector<int> groupMembers;
    for(size_t groupSize = 1; groupSize <= arr.size(); ++groupSize) {
        retV += traversalSum(arr, groupMembers, groupSize);
    }
    return retV % ((ull)pow(10,9) + 7);
}

ull xoringNinja(vector<int> arr) {
    ull r1 = 0, r2 = 1;
    ull m = (ull)(pow(10,9) + 7);
    for (size_t j = 0; j < arr.size(); ++j) {
        r1 |= arr[j];
        r1 %= m;
        if (j)
            r2 <<=1;
        r2 %=m;
    }
    return (r1 * r2)%m;
}

int main_()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int arr_count;
        cin >> arr_count;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(arr_count);

        for (int arr_itr = 0; arr_itr < arr_count; arr_itr++) {
            int arr_item = stoi(arr_temp[arr_itr]);

            arr[arr_itr] = arr_item;
        }

        ull result = xoringNinja(arr);

        fout << result << "\n";
    }

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

/*
Test input:
1
3
1 2 3
*/

string printBin(unsigned long long x) {
    unsigned long long a = (1 << 30);
    string o;
    ostringstream oo(o);
    while(a) {
        oo << ((x & a) == 0 ? 0 : 1);
        a >>= 1;
    }
    return oo.str();
}

int main() {
    srand (time(NULL));
    const unsigned long long t9 = (unsigned long long)pow(10,9);
    for(unsigned long long i = 0; i < 300; ++i) {
        unsigned long long a = rand() % t9, b = rand() % t9, c = rand() % t9;
        cout << "a:         " << printBin(a) << "\n";
        cout << "b:         " << printBin(b) << "\n";
        cout << "a + b:     " << printBin(a + b) << "\n";
        cout << "a ^ b:     " << printBin(a ^ b) << "\n";
        cout << "c:         " << printBin(c) << "\n";
        cout << "a + b + c: " << printBin(a + b + c) << "\n";
        cout << "a ^ c:     " << printBin(a ^ c) << "\n";
        cout << "b ^ c:     " << printBin(b ^ c) << "\n";
        cout << "a ^ b ^ c: " << printBin(a ^ b ^ c) << "\n";
        unsigned long long x = /*a + b + c +*/ (a ^ b) + (a ^ c) + (b ^ c) + (a ^ b ^ c);
        cout << x - (a + b + c) << "\n";
        x %= t9 + 7;
        cout << "xor sum:   " << printBin(x) << "\n";
        cout << string(80, '-') << "\n";
    }
    cout << t9 + 7 << "\n";
    cout << (t9 + 7) << "\n";
    cout << printBin(t9 + 7) << "\n";
}
