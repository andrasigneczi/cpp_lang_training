#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the hackerlandRadioTransmitters function below.
int hackerlandRadioTransmitters_(vector<int> x, int k) {
    sort(x.begin(), x.end());
    int trPos = x[0] + k;
    int lastTrPos = -1;
    int counter = 0;
    int firstOutOfRange = -1;
    for(size_t i = 1; i < x.size(); ++i) {
        if(trPos < x[i]) {
            ++counter;
            if(firstOutOfRange != -1 && firstOutOfRange >= x[i] - k) {
                trPos = x[i] + 2 * k + 1;
                lastTrPos = x[i];
            } else {
                trPos = x[i] + k;
                lastTrPos = x[i - 1];
            }
        } else if(trPos == x[i]) {
            ++counter;
            trPos = x[i] + 2 * k + 1;
            lastTrPos = x[i];
        }
        if(lastTrPos + k < x[i]) {
            firstOutOfRange = x[i];
        }
    }
    
    if(lastTrPos + k < x[x.size() - 1]) {
        ++counter;
    }
    
    if(x.size() == 1) counter = 1;
    
    return counter;
}

int hackerlandRadioTransmitters(vector<int> x, const int k) {
    if(x.size() == 1) return 1;

    set<int> xset;
    for(auto it = x.begin(); it != x.end(); ++it) {
        xset.insert(*it);
    }
    x.erase(x.begin(), x.end());
    for(auto it = xset.begin(); it != xset.end(); ++it) {
        x.push_back(*it);
    }
    
    int counter = 0;
    int trPos = -1;
    int left = -1;
    const int mp = 800;
    for(size_t i = 0; i < x.size(); ++i) {
        bool print = true;
        if(trPos == -1) {
            if(left == -1) {
                left = x[i];
                if(i < mp) {cout << "(" << left;}
                continue;
            }
            if(x[i] - left == k) {
                trPos = x[i];
                if(i < mp) {cout << "!" << trPos;print = false;}
                ++counter;
            } else if(x[i] - left > k) {
                if( x[i] - x[i - 1] <= k) {
                    trPos = x[i - 1];
                    ++counter;
                    if(x[i] - x[i - 1] == k) {
                        left = -1;
                        trPos = -1;
                        if(i < mp) {cout << "!" << x[i - 1] << " " << x[i] << ")" ;print = false;}
                    } else {
                        if(i < mp) {cout << "!" << trPos;}
                    }
                } else {
                    left = x[i];
                    if(i < mp) {cout << ");(" << left;print = false;}
                    ++counter;
                }
            }
        } else {
            if(x[i] - trPos == k && !(i + 1 < x.size() && x[i + 1] == x[i])) {
                trPos = -1;
                left = -1;
                if(i < mp) {cout << " " << x[i] << ")";print = false;}
            } else if(x[i] - trPos > k) {
                left = x[i];
                trPos = -1;
                if(i < mp) {cout << ");(" << left;print = false;}
            }
        }
        if(print && i < mp)
            cout << " " << x[i];
    }
    cout << ")\n";
    if(trPos == -1 && left != -1) {
        ++counter;
    }
    return counter;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string x_temp_temp;
    getline(cin, x_temp_temp);

    vector<string> x_temp = split_string(x_temp_temp);

    vector<int> x(n);

    for (int i = 0; i < n; i++) {
        int x_item = stoi(x_temp[i]);

        x[i] = x_item;
    }

    int result = hackerlandRadioTransmitters(x, k);

    fout << result << "\n";

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
