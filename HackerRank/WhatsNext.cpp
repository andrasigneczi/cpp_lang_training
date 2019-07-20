#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
using ull = unsigned long long;
/*
 * Complete the whatsNext function below.
 */

ull countOf1(const vector<int>& arr) {
    size_t oneCount = 0;
    for(size_t i = 0; i < arr.size(); i += 2) {
        oneCount += arr[i];
    }
    return oneCount;
}

ull inc(vector<int>& arr, ull oneCount) {
    if(arr.size() % 2 == 0 ) {
        // 0 ending
        ++oneCount;
        if(arr[arr.size() - 1] == 1) {
            // there is ony one zero at the end
            arr.erase(arr.end() - 1);
            ++arr[arr.size() - 1];
        } else {
            // there are more zeros at the end
            --arr[arr.size() - 1];
            arr.push_back(1);
        }
    } else {
        // 1 ending
        if(arr.size() == 1) {
            arr.push_back(arr[0]);
            arr[0] = 1;
            oneCount = 1;
        } else {
            oneCount -= arr[arr.size() - 1];
            ++oneCount;
            if(arr[arr.size() - 2] == 1) {
                // 10111 case, there is only 1 zero before tha last ones
                arr[arr.size() - 2] = arr[arr.size() - 1];
                arr.erase(arr.end() - 1);
                ++arr[arr.size() - 2];
            } else {
                // 1000111 case, there are more zeros before tha last ones
                int tmp = arr[arr.size() - 1];
                --arr[arr.size() - 2];
                arr[arr.size() - 1] = 1;
                arr.push_back(tmp);
            }
        }
    }
    return oneCount;
}

void whatsNext2(vector<int> arr) {
    /*
     * Write your code here.
     */
    // length of C
    // C
    const ull oc = countOf1(arr);
    ull ocNew = oc;

    do {
        ocNew = inc(arr, ocNew);
    } while(ocNew != oc);
    
    cout << arr.size() << "\n";
    copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";
}

void handleEvenArr(vector<ull>& arr) {
    // 1,1,1,1   1010       ==> 1100           *
    // 1,1,1,3   101000     ==> 110000
    // 1,1,3,1   101110     ==> 110011         *
    // 1,1,3,3   10111000   ==> 11000011
    // 1,3,1,1   100010     ==> 100100         *
    // 1,3,1,3   10001000   ==> 10010001
    // 1,3,3,1   10001110   ==> 10010011       *
    // 1,3,3,3   1000111000 ==> 1001000011
    // 3,1,1,1   111010     ==> 111100         *
    // 3,1,1,3   11101000   ==> 11110000
    // 3,1,3,1   11101110   ==> 11110011       *
    // 3,1,3,3   1110111000 ==> 1111000011
    // 3,3,1,1   11100010   ==> 11100100       *
    // 3,3,1,3   1110001000 ==> 1110010000
    // 3,3,3,1   1110001110 ==> 1110010011     *
    // 3,3,3,3   1110111000 ==> 1111000011
    if(arr[arr.size() - 1] == 1) {
        if(arr[arr.size() - 2] == 1) {
            if(arr[arr.size() - 3] == 1) {
                ++arr[arr.size() - 4];
                ++arr[arr.size() - 3];
                arr.erase(arr.end() - 2, arr.end());
            } else { // arr[arr.size() - 3] != 1
                --arr[arr.size() - 3];
                ++arr[arr.size() - 1];
            }
        } else { // arr[arr.size() - 2] != 1
            if(arr[arr.size() - 3] == 1) {
                ++arr[arr.size() - 4];
                ++arr[arr.size() - 3];
                --arr[arr.size() - 2];
                arr.erase(arr.end() - 1);
            } else { // arr[arr.size() - 3] != 1
                --arr[arr.size() - 3];
                ull tmp = arr[arr.size() - 2];
                arr[arr.size() - 2] = 1;
                ++arr[arr.size() - 1];
                arr.push_back(tmp - 1);
            }
        }
    } else { // arr[arr.size() - 1] != 1
        if(arr[arr.size() - 2] == 1) {
            if(arr[arr.size() - 3] == 1) {
                // 1,1,1,3   101000     ==> 110000
                // 3,1,1,3   11101000   ==> 11110000
                ++arr[arr.size() - 4];
                arr[arr.size() - 3] += arr[arr.size() - 1];
                arr.erase(arr.end() - 2, arr.end());
            } else { // arr[arr.size() - 3] != 1
                // 1,3,1,3   10001000   ==> 1001000
                // 3,3,1,3   1110001000   ==> 11100100000
                --arr[arr.size() - 3];
                ++arr[arr.size() - 1];
            }
        } else { // arr[arr.size() - 2] != 1
            if(arr[arr.size() - 3] == 1) {
                // 1,1,3,3   10111000   ==> 11000011
                // 3,1,3,3   1110111000 ==> 1111000011
                ++arr[arr.size() - 4];
                --arr[arr.size() - 2];
                arr[arr.size() - 3] += arr[arr.size() - 1];
                arr.erase(arr.end() - 1);
            } else { // arr[arr.size() - 3] != 1
                // 1,3,3,3   1000111000 ==> 1001000011
                // 3,3,3,3   111000111000 ==> 111001000011
                --arr[arr.size() - 3];
                ull tmp = arr[arr.size() - 2];
                arr[arr.size() - 2] = 1;
                ++arr[arr.size() - 1];
                arr.push_back(tmp - 1);
            }
        }
    }
}

void handleOddArr(vector<ull>& arr) {

    // 1,1,1     101       ==> 110
    // 1,1,3     10111     ==> 11011
    // 1,3,1     10001     ==> 10010
    // 1,3,3     1000111   ==> 1001011
    // 3,1,1     11101     ==> 11110
    // 3,1,3     1110111   ==> 1111011 
    // 3,3,1     1110001   ==> 1110010
    // 3,3,3     111000111 ==> 111001011
        
    if(arr[arr.size() - 1] == 1) {
        if(arr[arr.size() - 2] == 1) {
            ++arr[arr.size() - 3];
            arr.erase(arr.end() - 1);
        } else { // arr[arr.size() - 2] != 1
            --arr[arr.size() - 2];
            arr.push_back(1);
        }
    } else { // arr[arr.size() - 1] != 1
        if(arr[arr.size() - 2] == 1) {
            ++arr[arr.size() - 3];
            --arr[arr.size() - 1];
        } else { // arr[arr.size() - 2] != 1
            --arr[arr.size() - 2];
            ulong tmp = arr[arr.size() - 1];
            arr[arr.size() - 1] = 1;
            arr.push_back(1);
            arr.push_back(tmp - 1);
        }
    }
}

void whatsNext(vector<ull> arr) {
    if(arr.size() == 1) {
        if(arr[0] == 1) {
            // 1 ==> 1, 1     1 ==> 10
            arr.push_back(1);
        } else {
            // 3 ==> 1, 1, 2   111 ==> 1011
            arr.push_back(1);
            arr.push_back(arr[0]-1);
            arr[0] = 1;
        }
    } else if(arr.size() == 2) {
        if(arr[0] == 1) {
            // 1,1 ==> 2, 1        10 ==> 100
            ++arr[1];
        } else {
            // 3,1 ==> 1, 2, 2     1110   ==> 10011
            // 3,3 ==> 1, 3, 2     111000 ==> 1000011
            ull tmp1 = arr[arr.size() - 2];
            ull tmp2 = arr[arr.size() - 1];
            arr[0] = 1;
            arr[1] = tmp2 + 1;
            arr.push_back(tmp1 - 1);
        }
    } else {
        if(arr.size() % 2 == 1) {
            handleOddArr(arr);
        } else {
            handleEvenArr(arr);
        }
    }
    cout << arr.size() << "\n";
    copy(arr.begin(), arr.end() -1, ostream_iterator<ull>(cout, " "));
    cout << arr[arr.size() - 1] << "\n";
}

int main()
{
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

        vector<ull> arr(arr_count);

        for (int arr_itr = 0; arr_itr < arr_count; arr_itr++) {
            ull arr_item = stoull(arr_temp[arr_itr]);

            arr[arr_itr] = arr_item;
        }

        whatsNext(arr);
    }

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
