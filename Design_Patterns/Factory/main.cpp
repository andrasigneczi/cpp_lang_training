#include <iostream>
#include <memory>

class Currency {
public:
    virtual std::string_view name() = 0;
    virtual ~Currency() {}
};

class EUR : public Currency {
public:
    std::string_view name() override { return "Euro"; }
};


class USD : public Currency {
public:
    std::string_view name() override { return "USA dollar"; }
};

class SEK : public Currency {
public:
    std::string_view name()  override { return "Sweden Krona"; }
};

class CurrencyFactory {
    CurrencyFactory() {}
public:
    static std::unique_ptr<Currency> generateCurrency(std::string_view curr) {
	if(curr == "EUR") return std::make_unique<EUR>();
	else if(curr == "USD") return std::make_unique<USD>();
	else if(curr == "SEK") return std::make_unique<SEK>();
	return nullptr;
    }
};

int main(int argc, char* argv[]) {
    std::unique_ptr<Currency> c = CurrencyFactory::generateCurrency("EUR");
    std::cout << c->name() << "\n";
    c = CurrencyFactory::generateCurrency("SEK");
    std::cout << c->name() << "\n";
    c = CurrencyFactory::generateCurrency("USD");
    std::cout << c->name() << "\n";
    return 0;
}
