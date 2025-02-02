#include <iostream>
#include <iomanip>
#include "CrossPlatFuncs.h"
#include "Generators.h"
#include "Cases.h"
#include "InventorySystem.h"
#include "EventSystem.h"
#include "Player.h"

using namespace std;

Player::Player () :
    action_taken(false),
    day(0),
    winnings(1.0f),
    luck(1.0f),
    event_flags(0),
    inventory() 
{}

void Player::Header () {
    cout << "Winnings: " << std::fixed << winnings << "$    ";
    cout << "Luck: " << std::fixed << luck << "    ";
    cout << ( (!event_flags) ? "Big Chungus" : PrintEvent() ) << endl;
    cout << endl;
}

float Player::DoRoll () {
    action_taken = true;

    float r = gen::random() * luck;

    if (r > 1.00f) {
        r = 1.00f;
    } else if (r < 0.00f) {
        r = 0.00f;
    }

    return r;
}

bool Player::SellCase (const Case& _case) {
    ClearScreen();

    printf("Selling case [%s] for %.2f$\n", _case.case_name.c_str(), _case.price);
    printf("(y/n)?\n");
    
    char choice = GetChar();

    if (!(choice == 'y' || choice == 'Y')) return false;

    ShowRollLinear(_case.price);

    winnings += _case.price;
    printf("+%.2f$\nYou wasted a gambling opportunity.. lame..", _case.price);
    WaitInp("press enter..");
    return true;
}

void Player::OpenCase (const Case& _case) {
    ClearScreen();

    float roll = DoRoll();
    ShowRoll(roll);

    cout << "ROLL: " << roll << "\t|\tCASE: " << _case.threshold << endl;

    if (roll > 0.9) {
        printf("+0.05 LUCK\n");
        luck += 0.05;
    } else if (roll < 0.1) {
        printf("-0.05 LUCK\n");
        luck -= 0.05;
    }

    if (roll > _case.threshold) {
        winnings += _case.money_potential;
        cout << "BINGO!!\n+" << _case.money_potential << "$" << endl;
    } else {
        float returns = (_case.money_potential * roll) / (_case.threshold * 2.0f);
        winnings += returns;
        cout << "Returns: " << returns << "$" << endl;
    }

    WaitInp("press enter..");
}

void Player::BigGamba () {
    // Check first if player can big gamba
    if (winnings < 10) {
        cout << "You need to have at least 10$ to enter Big Gamba..";
        WaitInp("press enter..");
        return;
    }

    ClearScreen();

    float biggambaT = (event_flags == EVENT_LOWERALLIN)? 0.4f : 0.5f;
    float leniency = 0.10f;

    cout << "Welcome to Big Gamba where you gamble all your money in a double or nothing scenario." << endl;
    cout << "You have to roll more than a " << biggambaT << " to double your money!" << endl;
    cout << "If you roll any less, you will lose all your money." << endl;
    cout << "You're allowed to retain 10\% of your funds as an act of leniency." << endl;
    cout << "If you buy an insurance for 5$ before rolling for the all in, you will get to keep 50\% if you lose instead" << endl;

    cout << "\nAll in?\n( [y] : yes, [i] : yes with insurance, [n] : no, go back (default) )" << endl;

    char choice = GetChar();

    if (choice == 'y' || choice == 'Y') {

    } else if (choice == 'i' || choice == 'I') {
        if (winnings > 5.0f) {
            winnings -= 5.0f;
            leniency = 0.50f;
        } else {
            ClearScreen();
            printf("Not enough money: %.2f$\nInsurance costs: %.2f$", winnings, 5.0f);
            WaitInp("press enter..");
            return;
        }
    } else {
        return;
    }

    float roll = DoRoll();
    ShowRoll(roll);

    cout << "ROLL: " << roll << "\t|\tWIN: " << biggambaT << endl;

    if (roll > 0.9) {
        printf("+0.05 LUCK\n");
        luck += 0.05;
    } else if (roll < 0.1) {
        printf("-0.05 LUCK\n");
        luck -= 0.05;
    }

    if (roll > biggambaT) {
        winnings *= 2;
        if (roll > 0.9) {
            cout << "$$ ULTRA GAMBA WINNER $$" << endl;
        } else {
            cout << "BIG GAMBA WINNER!!" << endl;
        }
        WaitMs(800);
        cout << "+" << (winnings/2) << "$" << endl;
    } else {
        winnings *= leniency;
        
        cout << "What.." << endl;
        WaitMs(1000);

        cout << "You literally just lost all your money.." << endl;
        WaitMs(1000);

        cout << "New Balance: " << winnings << endl;
        cout << endl;
        cout << "Do you quit yet?" << endl;
    }

    WaitInp("press enter to go back to menu..");
}

// Inventory Management

void Player::OpenCaseOnIndex (int index) {
    if (index >= Inventory::NUM_OF_SLOTS || index < 0) return;

    if (!inventory.slots[index].empty) {
        inventory.slots[index].empty = true;
        OpenCase(inventory.slots[index].Scase);
    }
}

void Player::SellCaseOnIndex (int index) {
    if (index >= Inventory::NUM_OF_SLOTS || index < 0) return;

    if (!inventory.slots[index].empty) {
        if (SellCase(inventory.slots[index].Scase)) {
            inventory.slots[index].empty = true;
        }
    }
}

void Player::BuyCase () {
    auto cd = CaseDistribution::Instance();

    while (1) {
        ClearScreen();

        Header();

        int i = 0;
        for (Case c : cd.cases) {
            printf("%d) ", i++);
            c.Print();
        }

        cout << "\nUsage:\n{buy} {case number}\n{exit}" << endl;
        cout << "Enter command: ";

        string inp = "";
        std::getline(cin, inp);

        string cmd;
        string arg;

        istringstream iss(inp);
        iss >> cmd >> arg;

        if (cmd == "exit") return;

        if (cmd != "" && arg != "") {
            int index;
            try{ index = stoi(arg); }
            catch(const exception& e) { continue; }

            if (cmd == "buy") {
                if (winnings > cd.cases[index].price) {
                    winnings -= cd.cases[index].price;
                    inventory.InsertCase(cd.cases[index]);
                    ClearScreen();
                    printf("Transaction successful!\nNew balance: %.2f$", winnings);
                    WaitInp("press enter..");
                } else {
                    ClearScreen();
                    printf("Not enough money: %.2f$\nCase costs: %.2f$", winnings, cd.cases[index].price);
                    WaitInp("press enter..");
                }
            }
        }
    }
}

void Player::ClearEvents () {
    switch (event_flags) {
        case 0:
            return;
            break;
        case EVENT_BADLUCK:
            EventSystem::BadLuck(true);
            break;
        case EVENT_GOODLUCK:
            EventSystem::GoodLuck(true);
            break;
        case EVENT_GUARANTEEDWIN:
            EventSystem::GuaranteedWin(true);
            break;
        case EVENT_HIGHRISK:
            EventSystem::HighRisk(true);
            break;
        case EVENT_LOWERALLIN:
            EventSystem::LowerAllIn(true);
            break;
        default:
            cout << "EVENT: " << event_flags << "NOT IMPLEMENTED" << endl;
            WaitInp("");
    }

    event_flags = 0;
}

std::string Player::PrintEvent () {
    switch (event_flags) {
        case EVENT_BADLUCK:
            return "Bad Luck";
        case EVENT_GOODLUCK:
            return "Good Luck";
        case EVENT_GUARANTEEDWIN:
            return "Guaranteed Win";
        case EVENT_HIGHRISK:
            return "High Risk";
        case EVENT_LOWERALLIN:
            return "Big Gamba Day";
        default:
            return "UNIMPLEMENTED";
    }
}