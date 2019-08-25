#include <iostream>
#include <memory>

#if __cplusplus <201400L
namespace std {
    template<class T, class... Args>
    unique_ptr<T> make_unique(Args&&... args) {
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif

// ATM cash exchange
class Exchanger {
public:
    Exchanger() : bankNoteCount(0) {}
    virtual ~Exchanger() {}
    unsigned int process(unsigned int money) {
	money = handle(money);
	if(nextExchanger != nullptr) return nextExchanger->process(money);
	return money;
    }
    void setNext(std::unique_ptr<Exchanger>&& e) { nextExchanger = std::move(e); }

protected:
    virtual unsigned int handle(unsigned int money) = 0;
    unsigned int bankNoteCount;
    std::unique_ptr<Exchanger> nextExchanger;
};


class BankNote500 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 500;
	std::cout << bankNoteCount << " piece of $500\n";
	return money - bankNoteCount * 500;
    }
};


class BankNote200 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 200;
	std::cout << bankNoteCount << " piece of $200\n";
	return money - bankNoteCount * 200;
    }
};

class BankNote100 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 100;
	std::cout << bankNoteCount << " piece of $100\n";
	return money - bankNoteCount * 100;
    }
};

class BankNote50 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 50;
	std::cout << bankNoteCount << " piece of $50\n";
	return money - bankNoteCount * 50;
    }
};

class BankNote20 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 20;
	std::cout << bankNoteCount << " piece of $20\n";
	return money - bankNoteCount * 20;
    }
};

class BankNote10 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 10;
	std::cout << bankNoteCount << " piece of $10\n";
	return money - bankNoteCount * 10;
    }
};

class BankNote5 : public Exchanger {
public:
    unsigned int handle(unsigned int money) override {
	bankNoteCount = money / 5;
	std::cout << bankNoteCount << " piece of $5\n";
	return money - bankNoteCount * 5;
    }
};

class ATM {
public:
    ATM() {
	exchanger = std::make_unique<BankNote500>();
	std::unique_ptr<Exchanger> bn200 = std::make_unique<BankNote200>();
	std::unique_ptr<Exchanger> bn100 = std::make_unique<BankNote100>();
	std::unique_ptr<Exchanger> bn50 = std::make_unique<BankNote50>();
	std::unique_ptr<Exchanger> bn20 = std::make_unique<BankNote20>();
	std::unique_ptr<Exchanger> bn10 = std::make_unique<BankNote10>();
	std::unique_ptr<Exchanger> bn5 = std::make_unique<BankNote5>();
	bn10->setNext(std::move(bn5));
	bn20->setNext(std::move(bn10));
	bn50->setNext(std::move(bn20));
	bn100->setNext(std::move(bn50));
	bn200->setNext(std::move(bn100));
	exchanger->setNext(std::move(bn200));
    }

    void exchangeMoney(unsigned int money) {
	std::cout << exchanger->process(money) << " piece of $1\n";
    }
private:
    std::unique_ptr<Exchanger> exchanger;
};

int main(int argc, char* argv[]) {
    ATM atm;
    atm.exchangeMoney(1999);
    return 0;
}
