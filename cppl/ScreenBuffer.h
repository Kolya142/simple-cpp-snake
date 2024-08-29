#pragma once
#include "point.h"
#include <cstdint>
class ScreenBuffer {
private:
    char* buffer;
public:
    const uint16_t width = 120;
    const uint16_t height = 30;
    ScreenBuffer() : buffer(nullptr) {}
    ~ScreenBuffer() { delete[] buffer; }
    void Clear();
    bool DrawPoint(Point* pt, char c);
    bool DrawPoint(uint16_t x, uint16_t y, char c);
    void Draw();
};