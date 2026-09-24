#include <iostream>
#include <streambuf>
#include <vector>
#include <string>

#define main original_main
#include "main_test.cpp"
#undef main

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