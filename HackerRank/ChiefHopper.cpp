#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
using ull = unsigned long long;

// Complete the chiefHopper function below.
ull chiefHopper(vector<int> arr) {
    // bE1
    // bE2 = bE1 + (bE1 - h1) = 2bE1 - h1
    // bE3 = bE2 + (bE2 - h2) = 4bE1 - 2h1 - h2
    // bE4 = bE3 + (bE3 - h3) = 8bE1 - 4h1 - 2h2 - h3
    
    //ull heights = 0;
    //ull m = 1;
    ull bE = 0;
    ull sum = 0;
    for(size_t i = 0; i < arr.size(); ++i) {
        //heights = heights * 2 + arr[i];
        //m <<= 1;
        //bE = max(bE, (ull)ceil((long double)heights/(long double)m));
        if(2 * sum < arr[i]) {
            // pow(2.,i + 1) * (bE + a) - arr[i]  ==> a
            // sum = 2 * sum_prev - arr[i]
            // sum_prev = pow(2.,i) * bEd1
            if(i > 16) {
                return bE + 1;
            }
            //cout << i << ": " << arr[i] - 2 * sum << endl;
            ull a = (ull)ceil( (double)(arr[i] - 2 * sum) / pow(2.,i + 1));
            bE += a;
            sum = 2 * sum + a * pow(2.,i + 1) - arr[i];
            // cout << pow(2.,i + 1) << endl;
            // cout << "arr[i]: " << arr[i] << endl;
            // cout << "a: " << a << endl;
            // cout << "bE: " << bE << endl;
            // cout << "sum: " << sum << endl;
            // cout << string(10, '-') << endl;
        } else {
            sum = 2 * sum - arr[i];
        }
    }
    return bE;
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

    ull result = chiefHopper(arr);

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
