// My Drive >> Development >> Java >> Design Patterns
// Clean C++ page 245
// Effective modern C++ page 131

#include <iostream>
#include <set>
#include <memory>

class SubjectIF;
using SubjectPtr = std::shared_ptr<SubjectIF>;

class ObserverIF {
public:
    virtual ~ObserverIF() = default;
    virtual void notify(SubjectPtr subject) = 0;
};

using ObserverPtr = std::shared_ptr<ObserverIF>;

class SubjectIF : public std::enable_shared_from_this<SubjectIF> {
public:
    virtual void add(const ObserverPtr& observer) {
	observers.insert(observer);
    }

    virtual void remove(const ObserverPtr& observer) {
	observers.erase(observer);
    }

    virtual void notify() {
	for(auto& observer : observers) {
	    observer->notify(shared_from_this());
	}
    }

    virtual int observerNumber() const { return observers.size(); }

private:
    std::set<ObserverPtr> observers;
};


class Clock : public SubjectIF {
public:
    void tick50Times() {
	for(int i = 0; i < 50; ++i) {
	    notify();
	}
    }
};

class Cooker : public ObserverIF {
public:
    Cooker() : cookingOn(false) {}

    void cookingTimeInSec(int sec) {
	cookingOn = true;
	seconds = sec;
    }

    void notify(SubjectPtr subject) override {
	if(!cookingOn) return;
	std::cout << "Cooking ..." << seconds-- << "\n";
	if(seconds == 0) {
	    std::cout << "Ready\n";
	    cookingOn = false;
	}
    }

private:
    int seconds;
    bool cookingOn;
};

int main(int argc, char* argv[]) {
    std::shared_ptr<Clock> clock = std::make_shared<Clock>();

    std::shared_ptr<Cooker> cooker1 = std::make_shared<Cooker>();
    std::shared_ptr<Cooker> cooker2 = std::make_shared<Cooker>();

    clock->add(cooker1);
    clock->add(cooker2);

    cooker1->cookingTimeInSec(40);
    cooker2->cookingTimeInSec(20);
    clock->tick50Times();

    clock->remove(cooker2);
    clock->remove(cooker1);
    std::cout << clock->observerNumber() << "\n";

    return 0;
}
