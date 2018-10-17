#include <bits/stdc++.h>

/*
example input:

XXXXXX-XXX
XX------XX
XXXXXX-XXX
XXXXXX-XXX
XXX------X
XXXXXX-X-X
XXXXXX-X-X
XXXXXXXX-X
XXXXXXXX-X
XXXXXXXX-X
ICELAND;MEXICO;PANAMA;ALMATY

*/

using namespace std;

vector<string> split_string(string);

struct Node {
    int x;
    int y;
    bool victory;
    vector<Node> children;
    bool operator()(const Node& n1, const Node& n2) {
        if(n1.x == n2.x) {
            return n1.y < n2.y;
        }

        return n1.x < n2.x;
    }
};

bool isGoal(Node& n) {
    if((n.x == 1 || n.x == 2) && (n.y == 1 || n.y == 2)) {
        return true;
    }
    return false;
}
size_t nodeCount = 0;
void extract(Node& act) {
    //cout << "extract: x: " << act.x << " y: " << act.y << endl;
    for(int i = 0; i < 4; ++i) {
        int xX = act.x;
        int yY = act.y;
        switch(i) {
            case 0: xX -= 2; yY -= 1; break;
            case 1: xX -= 2; yY += 1; break;
            case 2: xX += 1; yY -= 2; break;
            case 3: xX -= 1; yY -= 2; break;
        }
        if(!(xX <= 0 || xX > 15 || yY <= 0 || yY > 15)) {
            //cout << "test: x: " << xX << " y: " << yY << endl;
            Node n{xX, yY, false};
            act.children.push_back(n);
            ++nodeCount;
        }
    }
}

void traversal(Node& act) {
    extract(act);
    for(size_t i = 0; i < act.children.size(); ++i) {
        traversal(act.children[i]);
    }
}

// calculation from the first player's point of view
void markGoals(Node& node, int level = 0) {
    for(size_t i = 0; i < node.children.size(); ++i) {
        markGoals(node.children[i], level + 1);
    }

    if(node.children.size() == 0) {
        if((level % 2) == 0) {
            node.victory = false; // the first one lost
        } else {
            node.victory = true; // the first one won
        }
    } else {
        if((level % 2) == 0) {
            // at least one node had to win
            for(size_t i = 0; i < node.children.size(); ++i) {
                if(node.children[i].victory) {
                    node.victory = true;
                    break;
                }
            }
        } else {
            // all of the nodes had to win
            size_t victories = 0;
            for(size_t i = 0; i < node.children.size(); ++i) {
                if(node.children[i].victory) {
                    ++victories;
                }
            }
            if(victories == node.children.size()) {
                node.victory = true;
            }
        }
    }
}

void printNode(Node& node, int level = 0) {
    cout << string(level, '-') << "victory: " << node.victory;
    cout << " children count: " << node.children.size() << "\n";
    cout << string(level, '-') << "x: " << node.x << " y: " << node.y;
    cout << "\n";
}

void printTree(Node& node, int level = 0) {
    printNode(node, level);
    for(size_t i = 0; i < node.children.size(); ++i) {
        printTree(node.children[i], level + 2);
    }
}

struct Node2 {
    int x;
    int y;
    bool victory;
    bool touched;
    vector<int> children;
};

void extract2(Node2& act) {
    //cout << "extract: x: " << act.x << " y: " << act.y << endl;
    for(int i = 0; i < 4; ++i) {
        int xX = act.x;
        int yY = act.y;
        switch(i) {
            case 0: xX -= 2; yY -= 1; break;
            case 1: xX -= 2; yY += 1; break;
            case 2: xX += 1; yY -= 2; break;
            case 3: xX -= 1; yY -= 2; break;
        }
        if(!(xX < 0 || xX >= 15 || yY < 0 || yY >= 15)) {
            //cout << "test: x: " << xX << " y: " << yY << endl;
            act.children.push_back(yY * 15 + xX);
        }
    }
}

vector<Node2> availableNodes(225);
void prepareAvailableNodes() {
    for(int i = 0; i < 15; ++i) {
        for(int j = 0; j < 15; ++j) {
            availableNodes[i * 15 + j].x = i;
            availableNodes[i * 15 + j].y = j;
            availableNodes[i * 15 + j].victory = false;
            availableNodes[i * 15 + j].touched = false;
            extract2(availableNodes[i * 15 + j]);
        }
    }
}

void markGoals2(Node2& node, int level = 0) {
    if(node.touched) {
        return;
    }
    
    node.touched = true;
    
    for(size_t i = 0; i < node.children.size(); ++i) {
        Node2& n = availableNodes[node.children[i]];
        markGoals2(n, level + 1);
    }

    if(node.children.size() == 0) {
        if((level % 2) == 0) {
            node.victory = false; // the first one lost
        } else {
            node.victory = true; // the first one won
        }
    } else {
        if((level % 2) == 0) {
            // at least one node had to win
            for(size_t i = 0; i < node.children.size(); ++i) {
                Node2& n = availableNodes[node.children[i]];
                if(n.victory) {
                    node.victory = true;
                    break;
                }
            }
        } else {
            // all of the nodes had to win
            size_t victories = 0;
            for(size_t i = 0; i < node.children.size(); ++i) {
                Node2& n = availableNodes[node.children[i]];
                if(n.victory) {
                    ++victories;
                }
            }
            if(victories == node.children.size()) {
                node.victory = true;
            }
        }
    }
}

// Complete the chessboardGame function below.
string chessboardGame(int x, int y) {
    //Node2 root{y, x, false};
    Node2& root = availableNodes[(y - 1) * 15 + x - 1];

    //using namespace std::chrono;
    //auto t0 = high_resolution_clock::now();

    //traversal(root);
    prepareAvailableNodes();
    
    //auto t1 = high_resolution_clock::now();
    //std::cout << std::endl << duration_cast<milliseconds>(t1-t0).count() << " milliseconds passed\n";
    //t0 = t1;

    markGoals2(root);
    
    //t1 = high_resolution_clock::now();
    //std::cout << std::endl << duration_cast<milliseconds>(t1-t0).count() << " milliseconds passed\n";
    
    //printTree(root);
    //cout << nodeCount << "\n";
    cerr << "x: " << x << " y: " << y << endl;
    return root.victory ? "First" : "Second";
}

string chessboardGame_(int x, int y) {
    x=x%4; 
    y=y%4;
    if((y==0)||(y==3)||(x==0)||(x==3)) return "First";
    return "Second";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string xy_temp;
        getline(cin, xy_temp);

        vector<string> xy = split_string(xy_temp);

        int x = stoi(xy[0]);

        int y = stoi(xy[1]);

        string result = chessboardGame(x, y);

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
