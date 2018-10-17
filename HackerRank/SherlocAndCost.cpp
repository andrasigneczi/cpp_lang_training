#include <bits/stdc++.h>

using namespace std;

/*
Given array B. We must determine array A. For all i, A[i] <= B[i].
S = sum(2, N, abs(A[i] - A[i - 1])
S is miximized

Example:
--------
B = [1, 2, 3]

A=any of these
[1,1,1], [1,1,2], [1,1,3]
[1,2,1], [1,2,2], [1,2,3]

S=
|1-1| + |1-1| = 0	|1-1| + |2-1| = 1	|1-1| + |3-1| = 2
|2-1| + |1-2| = 2	|2-1| + |2-2| = 1	|2-1| + |3-2| = 2

S = 2
*/

vector<string> split_string(string);
using ull = unsigned long long;

ull Sum(const vector<int>& A) {
    ull s = 0;
    for(size_t i = 1; i < A.size(); ++i) {
        s += abs(A[i] - A[i - 1]);
    }
    return s;
}

vector<int> winner;
ull wS = 0;
// Complete the cost function below.
ull cost_all(vector<int>& B, size_t pos = 0) {
    ull s = Sum(B);
    if(s > wS) { wS = s; winner = B;}
    for(size_t i = pos; i < B.size(); ++i) {
        int v = B[i];
        for(int x = 1; x <= B[i]; ++x) {
            B[i] = 1;
            cost_all(B, i + 1);
        }
        B[i] = v;
    }
    return wS;
}

ull cost_simple(const vector<int>& B) {
    vector<int> A(B.size());
    for(size_t i = 0; i < A.size(); ++i) {
        if(i % 2 == 0) {
            A[i] = 1;
        } else {
            A[i] = B[i];
        }
    }
    
    ull s1 = Sum(A);
    for(size_t i = 0; i < A.size(); ++i) {
        if(i % 2 == 1) {
            A[i] = 1;
        } else {
            A[i] = B[i];
        }
    }
    ull s2 = Sum(A);
    return s1 >s2 ? s1 : s2;
}

ull max(ull a1, ull a2, ull a3) {
    return max(a1, max(a2, a3));
}

ull cost(const vector<int>& B) {
    // S1: sum of previous differences where A[i - 1] = 1
    // S2: sum of previous differences where A[i - 1] = B[i - 1]
    ull S1 = 0, S2 = 0;
    for(size_t i = 1; i < B.size(); ++i) {
        if( i == 1) {
            ull a1 = abs(B[i] - B[i - 1]);
            ull a2 = abs(B[i] - 1);
            ull a3 = abs(1 - B[i - 1]);
            
            ull maxA = max(a1, a2, a3);
            if(maxA == a1 || maxA == a2) {
                S2 = maxA;
                S1 = a3;
            } else {
                S1 = maxA;
                S2 = a1 > a2 ? a1 : a2;
            }
        } else {
            ull a1 = abs(B[i] - B[i - 1]);
            ull a2 = abs(B[i] - 1);
            ull a3 = abs(1 - B[i - 1]);
            
            if(S1 + a2 > S2 + a1) {
                if(S1 + a2 > S2 + a3) {
                    // max is S1 + a2
                    ull nS2 = S1 + a2;
                    S1 = S2 + a3;
                    S2 = nS2;
                } else {
                    // max is S2 + a3
                    ull nS1 = S2 + a3;
                    S2 = S1 + a2;
                    S1 = nS1;
                }
            } else {
                if(S2 + a1 > S2 + a3) {
                    // max is S2 + a1
                    ull nS2 = S2 + a1;
                    S1 = S2 + a3;
                    S2 = nS2;
                } else {
                    // max is S2 + a3
                    ull nS1 = S2 + a3;
                    S2 = S2 + a1;
                    S1 = nS1;
                }
            }
        }
    }
    
    return max(S1, S2);
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

        string B_temp_temp;
        getline(cin, B_temp_temp);

        vector<string> B_temp = split_string(B_temp_temp);

        vector<int> B(n);

        for (int i = 0; i < n; i++) {
            int B_item = stoi(B_temp[i]);

            B[i] = B_item;
        }
        
        //winner = vector<int>();
        //wS = 0;
        int result = cost(B);
        fout << result << "\n";
        //for_each(winner.begin(), winner.end(), [&fout](const int x){ fout << x << " ";});
        //fout << "\n";
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
