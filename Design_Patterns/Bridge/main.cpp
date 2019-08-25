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

class DrawAPI {
public:
    virtual void drawCircle(int radius, int x, int y) = 0;
};

class RedCircle : public DrawAPI {
public:
    void drawCircle(int radius, int x, int y) override {
	std::cout << "Drawing circle [color: red, radius: " << radius << ", x: " << x << ", y: " << y << "]\n";
    }
};

class GreenCircle : public DrawAPI {
public:
    void drawCircle(int radius, int x, int y) override {
	std::cout << "Drawing circle [color: green, radius: " << radius << ", x: " << x << ", y: " << y << "]\n";
    }
};


class Shape {
public:
    virtual void draw() = 0;

protected:
    Shape(std::unique_ptr<DrawAPI>&& drawAPI) : drawAPI(std::move(drawAPI)) {}
    std::unique_ptr<DrawAPI> drawAPI;
};


class Circle : public Shape {
public:
    Circle(int x, int y, int radius, std::unique_ptr<DrawAPI>&& drawAPI) : Shape(std::move(drawAPI)), x(x), y(y), radius(radius) {}
    void draw() { drawAPI->drawCircle(radius, x, y); }
private:
    int x;
    int y;
    int radius;
};

int main(int argc, char* argv[]) {
    Circle redCircle(100, 100, 10, std::make_unique<RedCircle>());
    Circle greenCircle(100, 100, 10, std::make_unique<GreenCircle>());
    
    redCircle.draw();
    greenCircle.draw();
    return 0;
}
