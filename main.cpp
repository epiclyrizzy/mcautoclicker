#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int targetcps;
int bpschance;

void blockhit() {
    if (std::uniform_int_distribution<int>(0, 99)(gen) < bpschance) {
        PostMessage(FindWindowA("LWJGL", nullptr), 0x204, 0, 0);
        PostMessage(FindWindowA("LWJGL", nullptr), 0x205, 0, 0);

    }
}

void changeConsoleTitle(const std::string& title) {
    SetConsoleTitle(title.c_str());
}


void titleChangeThread() {
    std::string titleCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=";

    size_t index = 0;

    while (true) {
        std::rotate(titleCharacters.begin(), titleCharacters.begin() + index, titleCharacters.end());

        std::string newTitle = titleCharacters.substr(0, 6);

        changeConsoleTitle(newTitle);
        Sleep(10);

        index = (index + 1) % titleCharacters.size();
    }
}


int main() {
    std::thread titleThread(titleChangeThread);


    std::cout << "github.com/epiclyrizzy\n";
    std::cout << "Target CPS:";
    std::cin >> targetcps;
    std::cout << "BPS Chance:";
    std::cin >> bpschance;

    while (true) {
        int mincps = targetcps - std::uniform_int_distribution<int>(2, 7)(gen);
        int maxcps = targetcps + std::uniform_int_distribution<int>(2, 7)(gen);

        int clickdelay = std::uniform_int_distribution<int>(4, 7)(gen);

        int delay = 1000 / targetcps;

        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && (GetAsyncKeyState(VK_OEM_COMMA) & 0x8000)) {
            PostMessage(FindWindowA("LWJGL", nullptr), 0x201, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(clickdelay));
            PostMessage(FindWindowA("LWJGL", nullptr), 0x202, 0, 0);

            blockhit();

            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }

    titleThread.join();

    return 0;
}
