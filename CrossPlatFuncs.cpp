#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>
#include <limits>

#include "CrossplatFuncs.h"

void ClearScreen () {
    #ifdef _WIN32
        // Windows cls
        system("cls");
    #else
        // Unix-like clear
        system("clear");
    #endif
}

void WaitMs (int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms);
    #endif
}

void WaitInp (std::string msg) {
    std::cout << std::endl;
    std::cout << msg;
    std::cin.get();
}

char GetChar () {
    std::string input;
    std::getline(std::cin, input);
    return input[0];
}

void ShowRollLinear (float roll) {
    float n = 0;
    float inc = roll / 50;
    float thresh = roll - inc;
    
    while (n < thresh) {
        ClearScreen();
        n += inc;
        std::cout << n;
    }

    ClearScreen();
    std::cout << roll;

    WaitMs(500);
    ClearScreen();
}

void ShowRoll (float roll) {
    for (int i = 0; i < 60; ++i) {
        ClearScreen();
        printf("0.%d%d", i%10, i%7);
        WaitMs(15);
    }

    ClearScreen();
    if (roll == 1.0) {
        printf("`*.'!!! [ %.2f ] !!!'.*`", roll);
        WaitMs(1000);
    } else if (roll > 0.9) {
        printf("%.2f\nDayum son :o", roll);
        WaitMs(800);
    } else {
        std::cout << roll;
        WaitMs(500);
    }

    ClearScreen();
}

float Crawl (float i, const float x, const float m) {
    if (x == i) return i;

    float sign = (x - i) / std::abs(x - i);
    
    float distance = std::min(m, std::abs(x - i));

    return i + sign * distance;
}