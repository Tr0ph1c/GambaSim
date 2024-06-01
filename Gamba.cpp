#include <iostream>
#include <iomanip>
#include <random>
#include "CrossplatFuncs.h"
#include "Generators.h"
#include "Player.h"
#include "InventorySystem.h"
#include "EventSystem.h"
#include "SaveSystem.cpp"

using namespace std;

Player player = Player();
bool ran_once = false;

void RageConfirm () {
    ClearScreen();
    cout << "Are you sure you want to rage quit?" << endl;
    cout << "You will lose all your progress." << endl;
    cout << "([y] : to confirm)" << endl;

    char choice = GetChar();

    if (choice == 'y' || choice == 'Y') {
        Rage();
        exit(0);
    } else {
        return;
    }
}

void inline Header () {
    cout << "Winnings: " << std::fixed << player.winnings << "$    ";
    cout << "Luck: " << std::fixed << player.luck << "    ";
    cout << ( (!player.event_flags) ? "Big Chungus" : player.PrintEvent() ) << endl;
    cout << endl;
}

void inline Menu () {
    cout << "Welcome to Gamba, what do you want to do?" << endl;
    cout << "1) Get Case" << endl;
    cout << "2) Open Inventory" << endl;
    cout << "3) All in" << endl;
    cout << "4) Take a Break" << endl;
    cout << "9) Rage Quit" << endl;
}

void InventoryMenu () {
    while (1) {
        ClearScreen();

        player.inventory.PrintInventory();

        cout << "\nUsage:\n{open/sell} {case number}\n{exit}" << endl;
        cout << "Enter command: ";

        string inp = "";
        std::getline(cin, inp);

        string cmd;
        string arg;

        istringstream iss(inp);
        iss >> cmd >> arg;

        if (cmd == "exit") return;

        if (cmd != "" && arg != "") {
            int slot_index;
            try{ slot_index = stoi(arg); }
            catch(const exception& e) { continue; }

            if (cmd == "open") {
                player.OpenCaseOnIndex(slot_index);
            } else if (cmd == "sell") {
                player.SellCaseOnIndex(slot_index);
            }
        }
    }
}

void MainMenu () {
    while (1) {
        ClearScreen();
        cout << std::setprecision(2);
        Header();
        Menu();
        
        char choice = GetChar();

        switch (choice) {
            case '1':
                player.BuyCase();
                break;
            case '2':
                InventoryMenu();
                break;
            case '3':
                player.BigGamba();
                break;
            case '4':
                Save(player); exit(0);
                break;
            case '9':
                RageConfirm();
                break;
            default: {}
        }

        if (player.action_taken) {
            player.action_taken = false;
            break;
        }
    }
}

void StatusMenu () {
    ClearScreen();
    cout << "Day: " << ++player.day << "    Winnings: " << player.winnings << "$    " << "Highscore: " << player.highscore << "$" << endl;
    cout << "Luck: " << player.luck << endl;
    WaitMs(500);
    cout << "Decay luck by 0.01.." << endl;
    player.luck = Crawl(player.luck, 1.00f);
    WaitMs(500);
    cout << "New Luck: " << player.luck << endl;
    WaitInp("press enter..");
}

void PickEvent () {
    if (gen::random() > 0.2 * player.luck) return;

    ClearScreen();
    cout << "This day has a special event!" << endl;
    EventSystem::RunEvent();
    WaitInp("press enter for the next day..");
}

int main () {
    Load(player);
    EventSystem::InitEvents(&player);

    while (1) {
        ClearScreen();
        if (player.day > 5 && ran_once) PickEvent();
        MainMenu();
        if (player.highscore < player.winnings) player.highscore = player.winnings;
        player.ClearEvents();
        StatusMenu();
        ran_once = true;
    }
}