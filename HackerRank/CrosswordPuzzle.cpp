#include <bits/stdc++.h>

using namespace std;

enum cwtype {
    HORIZONTAL,
    VERTICAL
};

struct PlaceHolder {
    int    startC;
    int    startR;
    int    length;
    bool   occupied;
    enum cwtype cwtype;
};

struct Operator {
    size_t placeHolderIdx;
    size_t wordIdx;
};

vector<int> fieldChecker;
void handleField(const vector<string>& crossword, size_t i, size_t j, bool& started, PlaceHolder& p, vector<PlaceHolder>& places, cwtype cwtype) {
    if(crossword[i][j] == '-') {
        if(started) {
            ++p.length;
        } else {
            if(cwtype == HORIZONTAL 
               && j + 1 < crossword[i].length() 
               && crossword[i][j + 1] == '-') {
                started = true;
                p.startC = j;
                p.startR = i;
                p.length = 1;
                p.cwtype = cwtype;
            } else if(cwtype == VERTICAL 
                      && i + 1 < crossword.size() 
                      && crossword[i + 1][j] == '-') {
                started = true;
                p.startC = j;
                p.startR = i;
                p.length = 1;
                p.cwtype = cwtype;
            }
        }
    } else {
        if(started) {
            started = false;
            if(p.length > 0) {
                places.push_back(p);
                p = PlaceHolder{-1, -1, 0, false, cwtype};
            }
        }
    }
}

void parseCrossword(vector<PlaceHolder>& places, const vector<string>& crossword) {
    PlaceHolder p{-1, -1, 0, false, HORIZONTAL};
    bool started = false;
    for(size_t i = 0; i < crossword.size(); ++i) {
        for(size_t j = 0; j < crossword[i].length(); ++j) {
            handleField(crossword, i, j, started, p, places, HORIZONTAL);
        }
        if(started) {
            started = false;
            if(p.length > 0) {
                places.push_back(p);
                p = PlaceHolder{-1, -1, 0, false, HORIZONTAL};
            }
        }
    }

    for(size_t i = 0; i < crossword[0].length(); ++i) {
        for(size_t j = 0; j < crossword.size(); ++j) {
            handleField(crossword, j, i, started, p, places, VERTICAL);
        }
        if(started) {
            started = false;
            if(p.length > 0) {
                places.push_back(p);
                p = PlaceHolder{-1, -1, 0, false, VERTICAL};
            }
        }
    }
}

std::vector<std::string> split(const std::string str, char sep) {
    std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;
    while (std::getline(f, s, sep)) {
        if(s.length() == 0) continue;
        strings.push_back(s);
    }
    return strings;
}

/*0123456789
0 +-++++++++
1 +-++++++++
2 +-++++++++
3 +-----++++
4 +-+++-++++
5 +-+++-++++
6 +++++-++++
7 ++------++
8 +++++-++++
9 +++++-++++
LONDON;DELHI;ICELAND;ANKARA
1 3 5 0 0
2 7 6 0 0
1 0 6 0 1
5 3 7 0 1
*/

bool fit(const string word, PlaceHolder& p, const vector<string>& crossword) {
    if(p.length != word.length() || p.occupied) {
        return false;
    }
    for(size_t i = 0; i < word.size(); ++i) {
        if(p.cwtype == HORIZONTAL) {
            if(crossword[p.startR][p.startC + i] != '-' 
               && crossword[p.startR][p.startC + i] != word[i]) {
                return false;
            }
        } else {
            if(crossword[p.startR + i][p.startC] != '-' 
               && crossword[p.startR + i][p.startC] != word[i]) {
                return false;
            }
        }
    }
    return true;
}

void updateFieldChecker() {
    // fieldChecker    
}

void stepBack(vector<string>& crossword, vector<PlaceHolder>& places, stack<Operator>& steps) {
    Operator o = steps.top();
    steps.pop();
    PlaceHolder& p = places[o.placeHolderIdx];
    p.occupied = false;
    
    for(size_t i = 0; i < p.length; ++i) {
        if(p.cwtype == HORIZONTAL) {
            if( --fieldChecker[p.startR * crossword[0].length() + p.startC + i] == 0) {
                crossword[p.startR][p.startC + i] = '-';
            }
        } else {
            if(--fieldChecker[(p.startR + i) * crossword[0].length() + p.startC]) {
                crossword[p.startR + i][p.startC] = '-';
            }
        }
    }
    //cout << "stepBack wordIdx: " << o.wordIdx << "\n";
    //cout << "stepBack placeHolderIdx: " << o.placeHolderIdx << "\n";
}

void copy(vector<string>& crossword, PlaceHolder& p, const string& word, 
          stack<Operator>& steps, size_t wordIdx, size_t placeIdx) {
    for(size_t i = 0; i < word.size(); ++i) {
        if(p.cwtype == HORIZONTAL) {
            crossword[p.startR][p.startC + i] = word[i];
            ++fieldChecker[p.startR * crossword[0].length() + p.startC + i];
        } else {
            crossword[p.startR + i][p.startC] = word[i];
            ++fieldChecker[(p.startR + i) * crossword[0].length() + p.startC];
        }
    }
    p.occupied = true;
    steps.push(Operator{placeIdx, wordIdx});
    //cout << "copy wordIdx: " << wordIdx << "\n";
    //cout << "copy placeIdx: " << placeIdx << "\n";
}

bool fillTheCrosswordPuzzle(vector<string>& crossword, vector<PlaceHolder>& places, vector<string>& wordsL, stack<Operator>& steps, int wordIdx = 0) {
    if( wordIdx >= wordsL.size()) {
        return false;
    }
    
    for(size_t j = 0; j < places.size(); ++j) {
        if(fit(wordsL[wordIdx], places[j], crossword)) {
            copy(crossword, places[j], wordsL[wordIdx], steps, wordIdx, j);
            //cout << "New\n";
            //copy(crossword.begin(), crossword.end(), ostream_iterator<string>(cout, "\n"));

            if( wordIdx == wordsL.size() - 1) {
                return true;
            }
            if(!fillTheCrosswordPuzzle(crossword, places, wordsL, steps, wordIdx + 1)) {
                stepBack(crossword, places, steps);
                //cout << "After step back\n";
                //copy(crossword.begin(), crossword.end(), ostream_iterator<string>(cout, "\n"));
            } else {
                return true;
            }
        }
    }
    return false;
}

// Complete the crosswordPuzzle function below.
vector<string> crosswordPuzzle(vector<string> crossword, const string words) {
    vector<PlaceHolder> places;
    fieldChecker = vector<int>(crossword.size() * crossword[0].length(), 0);
    
    parseCrossword(places, crossword);
    vector<string> wordsL = split(words, ';');
    stack<Operator> steps;
    fillTheCrosswordPuzzle(crossword, places, wordsL, steps);
    
    //for(size_t i = 0; i < places.size(); ++i) {
    //    cout << places[i].startC << " " << places[i].startR << " " << places[i].length 
    //        << " " << places[i].occupied << " " << places[i].cwtype << "\n";
    //}
    //for(size_t i = 0; i < wordsL.size(); ++i) {
    //    cout << wordsL[i] << " ";
    //}
    //cout << "\n";
    return crossword;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++) {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
