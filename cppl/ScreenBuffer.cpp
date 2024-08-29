#pragma once
#include "ScreenBuffer.h"
#include "Point.h"
#include <vcruntime_string.h>
#include <stdio.h>
void ScreenBuffer::Clear() {
    delete[] buffer;
    char* buff = new char[width * height + 1];
    memset(buff, ' ', size_t(width * height - 1));
    buff[width * height] = '\0';
    buffer = buff;
}
bool ScreenBuffer::DrawPoint(uint16_t x, uint16_t y, char c) {
    uint16_t p = x + y * width;
    if (p > (width * height) || p < 0) {
        return false;
    }
    buffer[p] = c;
    return true;
}
bool ScreenBuffer::DrawPoint(Point* pt, char c) {
    uint16_t x = pt->x;
    uint16_t y = pt->y;
    uint16_t p = x + y * width;
    if (p > (width * height) || p < 0) {
        return false;
    }
    buffer[p] = c;
    return true;
}
void ScreenBuffer::Draw() {
    printf("%s", buffer);
}