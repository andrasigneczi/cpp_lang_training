#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

// sorted vector from smallest size to highest size
struct GroupNode {
    int lastValue;
    int itemCount;
    size_t size() { return (size_t)itemCount; }
    int* rbegin() { return &lastValue; }
    void push_back(int val) { lastValue = val; ++itemCount; }
};

list<GroupNode>  groups;
int deleteMinGroupSize = -1;
void createNewGroup(int C);

void changeGroupPos(list<GroupNode>::iterator it) {
    while(next(it) != groups.end() && it->size() > next(it)->size()) {
        swap(*it, *next(it));
        ++it;
    }
}

bool addToAGroup(int C) {
    for(auto it = groups.begin(); it != groups.end(); ) {
        auto& pSet = *it;
        if(*pSet.rbegin() < C - 1) {
            if(deleteMinGroupSize == -1 || deleteMinGroupSize > (int)pSet.size()) {
                deleteMinGroupSize = (int)pSet.size();
            }
            it = groups.erase(it);
            continue;
        }
        
        if(*pSet.rbegin() == C - 1) {
            pSet.push_back(C);
            changeGroupPos(it);
            return true;
        }
        ++it;
    }
    return false;
}

void createNewGroup(int C) {
    GroupNode pSet{C, 1};
    groups.push_front(pSet);
}

void emptyGroups() {
    groups.erase(groups.begin(), groups.end());
    deleteMinGroupSize = -1;
}

void optimizeGroupSizes() {

}

int smallestGroupSize() {
    // cerr << "groupCount: " << groups.size() << endl;
    if(groups.size() > 0 || deleteMinGroupSize != -1) {
        if(deleteMinGroupSize != -1) {
            return min(deleteMinGroupSize, (int)groups.begin()->size());
        }
        return groups.begin()->size();
    }
    return 0;
}

int teamPerformation(vector<int>& contestants) {
    if(contestants.size() == 0) {
        return 0;
    }

    sort(contestants.begin(), contestants.end());
    for(size_t i = 0; i < contestants.size(); ++i) {
        int C = contestants[i];
        if(!addToAGroup(C)) {
            createNewGroup(C);
        }
    }
    
    optimizeGroupSizes();
    int retV = smallestGroupSize();
    emptyGroups();
    return retV;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int testCases;
    cin >> testCases;
    for(int i = 0; i < testCases; ++i) {
        int contestantCount;
        cin >> contestantCount;
        vector<int> contestants(contestantCount);
        for(int j = 0; j < contestantCount; ++j) {
            cin >> contestants[j];
        }
        cout << teamPerformation(contestants) << endl;
    }
    return 0;
}
