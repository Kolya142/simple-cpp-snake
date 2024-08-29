#include <iostream>
#include <chrono>
#include <cstdio>
#include <deque>
#include <vector>
#include <thread>
#include <windows.h>
#include "ScreenBuffer.h"
#include "Point.h"

void enableAnsiEscapeCodes() { // by chatgpt
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

bool IsKeyPressed(char c) {
    return GetAsyncKeyState(c) & 0x8000;
}

void keyupdate(int& vx, int& vy) {
    if (IsKeyPressed('A')) {
        vx = -1;
        vy = 0;
        return;
    }
    if (IsKeyPressed('W')) {
        vx = 0;
        vy = -1;
        return;
    }
    if (IsKeyPressed('S')) {
        vx = 0;
        vy = 1;
        return;
    }
    if (IsKeyPressed('D')) {
        vx = 1;
        vy = 0;
        return;
    }
}

void initapples(std::vector<Point*>& apples, uint16_t w, uint16_t h) {
    for (int i = 0; i < 20; i++) {
        apples.push_back(
            new Point(
                rand() % w, 
                rand() % h));
    }
}

int main()
{
    enableAnsiEscapeCodes();
    std::deque<Point*> ball_poses = {};
    std::vector<Point*> apples = {};
    ScreenBuffer* sb = new ScreenBuffer();
    initapples(apples, sb->width, sb->height);
    int y = 7;
    int x = 4;
    int vx = 0;
    int vy = 0;
    int snake_size = 2;
    std::cout << "\x1b[?25l";
    while (1) {
        x += vx;
        y += vy;
        if (x <= 0 || x >= sb->width) {
            vx *= -1;
        }
        if (y <= 0 || y >= sb->height) {
            vy *= -1;
        }
        if (IsKeyPressed(VK_ESCAPE)) {
            break;
        }
        keyupdate(vx, vy);
        ball_poses.push_back(new Point(x, y));
        if (ball_poses.size() > snake_size) {
            delete ball_poses[0];
            ball_poses.pop_front();
        }
        sb->Clear();
        int i = 0;
        for (Point* point : apples) {
            sb->DrawPoint(point, 'a');
            if (x == point->x && y == point->y) {
                delete point;
                apples.erase(apples.begin() + i);
                apples.push_back(
                    new Point(
                        rand() % sb->width,
                        rand() % sb->height));
                snake_size++;
            }
            else {
                i++;
            }
        }
        for (Point* point : ball_poses) {
            sb->DrawPoint(point, '.');
        }
        sb->DrawPoint(x, y, '*');
        std::cout << "\x1b[H";
        sb->Draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }
    for (Point* point : ball_poses) {
        delete point;
    }
    for (Point* point : apples) {
        delete point;
    }
    delete sb;
}