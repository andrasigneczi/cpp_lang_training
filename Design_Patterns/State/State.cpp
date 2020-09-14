#include <iostream>
#include <memory>

using namespace std;

class Subject;
class State_Step1;
class State_Step2;
class State_Ready;

class StateIF {
public:
    virtual bool isReady() { return false; }
    virtual void change( Subject* subject ) = 0;
};

class Subject {
public:
    Subject();
    void run();
    void setState( StateIF* state );
private:
    unique_ptr<StateIF> mState;
};

class State_Step1 : public StateIF {
public:
    void change( Subject* subject ) override;
};

class State_Step2 : public StateIF {
public:
    void change( Subject* subject ) override;
};

class State_Ready : public StateIF {
public:
    virtual bool isReady();
    void change( Subject* subject ) override;
};


class State_Start : public StateIF {
public:
    void change( Subject* subject ) override {
        // do things
        cout << "new state: Step1\n";
        subject->setState( new State_Step1 );
    }
};

void State_Step1::change( Subject* subject ) {
        // do things
        cout << "new state: Step2\n";
        subject->setState( new State_Step2 );
}


void State_Step2::change( Subject* subject ) {
        // do things
        cout << "new state: Ready\n";
        subject->setState( new State_Ready );
}

bool State_Ready::isReady() { return true; }
void State_Ready::change( Subject* subject ) {
        // do nothing
}


Subject::Subject() {}
void Subject::run() {
        setState( new State_Start());
        cout << "new state: Start\n";
        while( !mState->isReady()) {
            mState->change( this );
        }
    }
    
void Subject::setState( StateIF* state ) {
        mState.reset( state );
    }
    

int main( int argc, char* argv[] ) {
    Subject s;
    s.run();
}
