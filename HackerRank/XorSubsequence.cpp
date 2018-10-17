#include <bits/stdc++.h>

using namespace std;

/*
Xor every possible subsequnces, and find the higest frequency of the subresults.
output: 1. the smallest value from the numbers which have the highest frequency.
*/

/*
 * Complete the xorSubsequence function below.
 */
map<long, long> frequency;
void incFrequency(long x) {
    if(frequency.find(x) == frequency.end()) {
        frequency[x] = 1;
    } else {
        ++frequency[x];
    }
}

vector<int> xorSubsequence(vector<long> a) {
    /*
     * Write your code here.
     */
    for(size_t i = 0; i < a.size(); ++i) {
        incFrequency(a[i]);
    }
    
    //xoring the subsequencies
    for(size_t i = 0; i < a.size(); ++i) {
        incFrequency(a[i]);
    }
    
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<long> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        long a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<int> result = xorSubsequence(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
