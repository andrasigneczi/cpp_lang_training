#include <iostream>
#include <memory>

class Button {
public:
    virtual void paint() = 0;
};

class TextEdit {
public:
    virtual void paint() = 0;
};

class WinButton : public Button {
public:
    void paint() override {
        std::cout << "WinButton\n";
    }
};

class LinButton : public Button {
public:
    void paint() override {
        std::cout << "LinButton\n";
    }
};

class WinTextEdit : public TextEdit {
public:
    void paint() override {
        std::cout << "WinTextEdit\n";
    }
};

class LinTextEdit : public TextEdit {
public:
    void paint() override {
        std::cout << "LinTextEdit\n";
    }
};

class WidgetFactory {
public:
    virtual std::unique_ptr<Button> genButton() = 0;
    virtual std::unique_ptr<TextEdit> genTextEdit() = 0;
};

class LinWidgetFactory : public WidgetFactory{
public:
    std::unique_ptr<Button> genButton() override {
        return std::make_unique<LinButton>();
    }
    
    std::unique_ptr<TextEdit> genTextEdit() override {
        return std::make_unique<LinTextEdit>();
    }
};

class WinWidgetFactory : public WidgetFactory{
public:
    std::unique_ptr<Button> genButton() override {
        return std::make_unique<WinButton>();
    }
    
    std::unique_ptr<TextEdit> genTextEdit() override {
        return std::make_unique<WinTextEdit>();
    }
};


int main(int argc, char* argv[]) {

    std::unique_ptr<WidgetFactory> w = std::make_unique<LinWidgetFactory>();
    std::unique_ptr<Button> b = w->genButton();
    b->paint();
    return 0;
}