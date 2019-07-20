#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
typedef unsigned long long ull;

// Complete the nimGame function below.
string nimGame_(vector<int> pile, char player = 'f', int level = 0) {
    ull sum = 0;
    for(size_t i = 0; i < pile.size(); ++i) {
        sum += pile[i];
    }
    
    if(sum == 0) {
        if(player == 'f') {
            return "Second";
        } else {
            return "First";
        }
    }

    if(player == 'f') {
        player = 's';
    } else {
        player = 'f';
    }

    size_t victoryCount = 0;
    size_t defeatCount = 0;
    set<int> cache;
    for(size_t i = 0; i < pile.size(); ++i) {
        if(level % 2 == 0) {
            auto it = cache.find(pile[i]);
            if(it == cache.end()) {
                cache.insert(pile[i]);
            } else {
                continue;
            }
        }
        for(size_t j = 1; j <= pile[i]; ++j) {
            pile[i] -= j;
            string retv = nimGame_(pile, player, level + 1);
            if(retv == "First") {
                ++victoryCount;
            } else if(retv == "Second") {
                ++defeatCount;
            }
            pile[i] += j;
            if(level % 2 == 0 && victoryCount > 0) {
                goto end;
            }
        }
    }
end:
    if(level % 2 == 0) {
        if(level == 0) {
            copy(pile.begin(), pile.end(), ostream_iterator<int>(cerr, ","));
            cerr << "\n";
            cerr << "victoryCount: " << victoryCount << "\n";
            cerr << "defeatCount: " << defeatCount << "\n";
            cerr << string(50, '-') << endl;
        }
        // OR subtree, at least one victory necessary
        if(victoryCount > 0) {
            return "First";
        } else {
            return "Second";
        }
    } else {
        // AND subtree, all subtree must be victorious
        if(victoryCount > 0 && defeatCount == 0) {
            return "First";
        } else {
            return "Second";
        }
    }
    //cerr << "Something went wrong\n";
    return "";
}

string nimGame(vector<int> pile) {
    ull sum = 0;
    for(size_t i = 0; i < pile.size(); ++i) {
        sum ^= pile[i];
    }
    
    if(sum == 0) {
        return "Second";
    } else {
        return "First";
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int g;
    cin >> g;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int g_itr = 0; g_itr < g; g_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string pile_temp_temp;
        getline(cin, pile_temp_temp);

        vector<string> pile_temp = split_string(pile_temp_temp);

        vector<int> pile(n);

        for (int i = 0; i < n; i++) {
            int pile_item = stoi(pile_temp[i]);

            pile[i] = pile_item;
        }

        string result = nimGame(pile);

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
2
2
1 1
3
2 1 4
*/