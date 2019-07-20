#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

vector<string> split_string(string);

// Complete the sherlockAndMinimax function below.
int sherlockAndMinimax_(vector<int> arr, int p, int q) {
    set<int> arr2(arr.begin(), arr.end());
    int retVal = p;
    int maX = -1;
    int beg = p;
    int end = q;
    
    // special cases
    if(*arr2.begin() >= q) {
        return p;
    } else if(*prev(arr2.end()) <= p) {
        return q;
    } else if(*arr2.begin() > p && *arr2.begin() < q) {
        retVal = p;
        maX = abs(p - *arr2.begin());
        beg = *arr2.begin();
    }
    
    for(int i = beg; i <= end; ++i) {
        auto it = arr2.lower_bound(i);
        if(it == arr2.end()) {
            /*
            int tmp = max(maX, abs(i - *prev(arr2.end())));
            if(tmp != maX) {
                maX = tmp;
                retVal = i;
            }
            */
            int tmp = max(maX, abs(q - *prev(arr2.end())));
            if(tmp != maX) {
                maX = tmp;
                retVal = q;
            }
            break;
        } else {
            if(*it != i) {
                // I need the min of prev and this one
                auto prv = prev(it);
                int tmp;
                if(prv != arr2.end()) {
                    int m = min(abs(i - *prv), abs(i - *it));
                    tmp = max(maX, m);
                } else {
                    tmp = max(maX, abs(i - *it));
                }
                if(tmp != maX) {
                    maX = tmp;
                    retVal = i;
                }
            } else {
                // min() = 0, nothin to do
            }
        }
        //cout << "i: " << i << " maX: " << maX << " retVal: " << retVal << "\n";
    }
    return retVal;
}

int sherlockAndMinimax(vector<int> arr, int p, int q) {
    set<int> arr2(arr.begin(), arr.end());
    int retVal = p;
    int maX = -1;
    int beg = p;
    int end = q;
    
    // special cases
    if(*arr2.begin() >= q) {
        return p;
    } else if(*prev(arr2.end()) <= p) {
        return q;
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    string pq_temp;
    getline(cin, pq_temp);

    vector<string> pq = split_string(pq_temp);

    int p = stoi(pq[0]);

    int q = stoi(pq[1]);

    int result = sherlockAndMinimax(arr, p, q);

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
