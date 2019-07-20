#ifndef __TPRINTF__H
#define __TPRINTF__H
#include <iostream>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    std::cout << "\nsize: " << sizeof...(Fargs) << "\n";
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           std::cout << value;
           tprintf(format+1, Fargs...); // recursive call
           return;
        }
        std::cout << *format;
    }
}

#endif // __TPRINTF__H

// c++17
// template <typename... bases>
// struct X : bases... {
// 	using bases::g...;
// };
// X<B, D> x; // OK: B::g and D::g introduced


/**************************************************************
*********************template specialization*******************
***************************************************************/
template<int... A>
class TestTemplate1 {
public:

    std::string getString() {
        return "Normal";
    }
};

template<int... A>
class TestTemplate1<2, A...> { // Define a class specialization
public:
    std::string getString() {
        return "Specialized";
    }
};

/**************************************************************
*********************vaiadic template traversal****************
***************************************************************/
template<int val> struct value{
    operator int(){return val;}
};

template <typename...I> struct container {
    container(){
        int array[sizeof...(I)]={I()...};
        printf("container<");
        for(int count = 0; count < sizeof...(I); count++){
            if(count>0){
                printf(",");
            }
            printf("%d", array[count]);
        }
        printf(">\n");
    }
};

int main()
{
    tprintf("% world% %\n","Hello",'!',123);
    
    // template specialization test
    TestTemplate1<1, 2, 3, 4> t1_1;
    TestTemplate1<1, 2> t1_2;
    TestTemplate1<> t1_3;
    TestTemplate1<2, 2> t1_4;

    std::cout << t1_1.getString() << std::endl;
    std::cout << t1_2.getString() << std::endl;
    std::cout << t1_3.getString() << std::endl;
    std::cout << t1_4.getString() << std::endl;

    // variadic template traversal
    container<value<9>, value<19>, value<29>, value<99>> tt;
    return 0;
}
