#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
typedef unsigned long long ull;

// Complete the boardCutting function below.
int boardCutting(vector<int> cost_y, vector<int> cost_x) {
    const ull M = (ull)pow(10,9) + 7;
    sort(cost_y.begin(), cost_y.end(), greater<int>());
    sort(cost_x.begin(), cost_x.end(), greater<int>());
    
    ull minTotalCost = 0;
    ull horizontalPieces = 1;
    ull verticalPieces = 1;
    long long cost1, cost2;
    auto it1 = cost_y.begin();
    auto it2 = cost_x.begin();
    while(true) {
        cost1 = -1;
        cost2 = -1;
        if(it1 != cost_y.end()) {
            cost1 = (*it1) * verticalPieces;
        }
        
        if(it2 != cost_x.end()) {
            cost2 = (*it2) * horizontalPieces;
        }
        
        if(cost1 == -1 && cost2 == -1) {
            break;
        }
        
        if(cost1 != -1 && cost2 != -1) {
            if(*it1 >= *it2) {
                ++horizontalPieces;
                it1 = next(it1);
                minTotalCost += cost1;
            } else {
                ++verticalPieces;
                it2 = next(it2);
                minTotalCost += cost2;
            }
        } else if(cost1 != -1) {
            minTotalCost += cost1;
            ++horizontalPieces;
            it1 = next(it1);
        } else if(cost2 != -1) {
            minTotalCost += cost2;
            ++verticalPieces;
            it2 = next(it2);
        }
    }
    return (minTotalCost % M);
}

int main_foreign_solution() {
    int q;
    cin >> q;
    
    while (q--) {
        // input each test case
        int m,n;
        cin >> m >> n;
        vector <pair<long,int>> c;
        long cost;
        for (int i=0;i<m-1;i++) {
            cin >> cost;
            c.push_back(make_pair(cost,1)); // 1 to indicate cy
        }
        for (int i=0;i<n-1;i++) {
            cin >> cost;
            c.push_back(make_pair(cost,0)); // 0 to indicate cx
        }
        
        // sort combined costs of y and x
        sort(c.begin(),c.end());
        reverse(c.begin(),c.end());
        
        int yCut=1;
        int xCut=1;
        long totalCost=0;
        for (int i=0;i<c.size();i++) {
            if (c[i].second) { // y-cut
                totalCost+=(c[i].first*xCut);
                yCut++;
            }
            else { // x-cut
                totalCost+=(c[i].first*yCut);
                xCut++;                
            }
        }
        cout << totalCost%1000000007 << endl;
    }
    
    return 0;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string mn_temp;
        getline(cin, mn_temp);

        vector<string> mn = split_string(mn_temp);

        int m = stoi(mn[0]);

        int n = stoi(mn[1]);

        string cost_y_temp_temp;
        getline(cin, cost_y_temp_temp);

        vector<string> cost_y_temp = split_string(cost_y_temp_temp);

        vector<int> cost_y(m-1);

        for (int i = 0; i < m-1; i++) {
            int cost_y_item = stoi(cost_y_temp[i]);

            cost_y[i] = cost_y_item;
        }

        string cost_x_temp_temp;
        getline(cin, cost_x_temp_temp);

        vector<string> cost_x_temp = split_string(cost_x_temp_temp);

        vector<int> cost_x(n-1);

        for (int i = 0; i < n-1; i++) {
            int cost_x_item = stoi(cost_x_temp[i]);

            cost_x[i] = cost_x_item;
        }

        int result = boardCutting(cost_y, cost_x);

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
