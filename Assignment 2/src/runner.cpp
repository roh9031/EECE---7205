#include <iostream>
#include <streambuf>


#define main original_main
#include "Assignment_2_FCE_Bidnurmath.cpp"
#undef main

// Echo buffer to mirror inputs to stdout
struct EchoBuf : std::streambuf {
    std::streambuf* src;
    char c;
    EchoBuf(std::streambuf* s) : src(s), c(0) {}
    int_type underflow() override {
        int_type ch = src->sbumpc();
        if (ch == traits_type::eof()) return ch;
        c = (char)ch;
        std::cout.put(c);
        setg(&c, &c, &c + 1);
        return traits_type::to_int_type(c);
    }
};


int main() {
    EchoBuf eb(std::cin.rdbuf());
    std::cin.rdbuf(&eb);
    return original_main();
}