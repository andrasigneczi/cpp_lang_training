#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
typedef unsigned long long ull;

/*
    Let ⊕ denote the bitwise xor operation on natural numbers. It is both well-known and easy to verify that a Nim position (n1,…,nk) is
    a second player win in misère Nim if and only if some ni>1 and n1⊕⋯⊕nk=0, or all ni≤1 and n1⊕⋯⊕nk=1.
*/
string misereNim(vector<int> pile, int level = 0) {
    ull sum = 0;
    size_t ones = 0;
    for(size_t i = 0; i < pile.size(); ++i) {
        sum ^= pile[i];
        ones += pile[i] == 1;
    }
    
    if((sum == 0 && ones != pile.size()) || (sum == 1 && ones == pile.size())) {
        return "Second";
    } else {
        return "First";
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string s_temp_temp;
        getline(cin, s_temp_temp);

        vector<string> s_temp = split_string(s_temp_temp);

        vector<int> s(n);

        for (int i = 0; i < n; i++) {
            int s_item = stoi(s_temp[i]);

            s[i] = s_item;
        }

        string result = misereNim(s);

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
