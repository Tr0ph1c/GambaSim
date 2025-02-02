#include <iostream>
#include <functional>
#include "Generators.h"
#include "Cases.h"
#include "Player.h"
#include "CrossplatFuncs.h"

#include "EventSystem.h"

using namespace std;

Player* EventSystem::player = nullptr;
std::vector<EventSystem::Event> EventSystem::events = {};

void EventSystem::RunEvent() {
    if (events.size() == 0) cout << "No events to load" << endl;

    int r = gen::random(0, events.size() - 1);
    events[r](false);
}

void EventSystem::InitEvents (Player* _player) {
    events.push_back(GoodLuck);
    events.push_back(FreeChest);
    events.push_back(GuaranteedWin);
    events.push_back(LowerAllIn);
    events.push_back(BadLuck);
    events.push_back(Robber);
    events.push_back(HighRisk);
    events.push_back(RollForYourLife);
    events.push_back(ResetLuck);

    player = _player;
}

void EventSystem::GoodLuck (bool exit) {
    if (!exit) {
        cout << "You gain +0.25 LUCK for the whole day!" << endl;
        player->event_flags = EVENT_GOODLUCK;
        player->luck += 0.25f;
    } else {
        player->luck -= 0.25f;
    }
}

void EventSystem::BadLuck (bool exit) {
    if (!exit) {
        cout << "You lose -0.2 LUCK till the end of the day." << endl;
        player->event_flags = EVENT_BADLUCK;
        player->luck -= 0.2f;
    } else {
        player->luck += 0.2f;
    }
}

void EventSystem::ResetLuck (bool exit) {
    cout << "Your luck is reset to (1.00)." << endl;
    player->luck = 1.00f;
}

void EventSystem::FreeChest (bool exit) {
    cout << "You get a random free chest!" << endl;
    WaitInp("press enter to reveal the chest..");
    auto C = CaseDistribution::CollectCase();
    cout << "** "; C.Print();
    player->inventory.InsertCase(C);
}

void EventSystem::GuaranteedWin (bool exit) {
    cout << "You are guaranteed to profit on your next case opening!" << endl;
    player->event_flags = EVENT_GUARANTEEDWIN;
}

void EventSystem::LowerAllIn (bool exit) {
    cout << "(ALL IN) has a lower threshold for this whole day! (0.4)" << endl;
    player->event_flags = EVENT_LOWERALLIN;
}

void EventSystem::Robber (bool exit) {
    cout << "A thief stole some of your money; 40\% of it to be precise.." << endl;
    cout << "-" << player->winnings * 0.40f << "$" << endl;
    player->winnings *= 0.60f;
    cout << "New balance: " << player->winnings << "$" << endl;
}

void EventSystem::HighRisk (bool exit) {
    if (!exit) {
        cout << "For this whole day, opening cases is more risky." << endl;
        player->event_flags = EVENT_HIGHRISK;
        for (auto C : CaseDistribution::Instance().cases) {
            C.threshold += 0.10f;
        }
    } else {
        for (auto C : CaseDistribution::Instance().cases) {
            C.threshold -= 0.10f;
        }
    }
}

void EventSystem::RollForYourLife (bool exit) {
    while (1) {
        ClearScreen();

        cout << "A mafia boss approached you demanding $30. Will you comply?" << endl;
        cout << "(y/n)" << endl;
        char choice = GetChar();

        if (choice == 'y' || choice == 'Y') {
            if (player->winnings > 30) {
                cout << "\nYou gave up 30$ for him to leave you." << endl;
                WaitMs(500);
                cout << "New Balance: " << player->winnings << "$" << endl;
                WaitMs(500);
            } else {
                ClearScreen();
                cout << "Not enough money (" << player->winnings << "$)" << endl;
                WaitInp("press enter..");
                continue;
            }
        } else if (choice == 'n' || choice == 'N') {
            cout << "\nNow you have to roll for your life." << endl;
            cout << "Press enter to roll.." << endl;

            float r = gen::random() * 1.10f;
            ShowRoll(r);

            cout << "ROLL: " << r << "\t|\tSURVIVE: " << 0.40f << endl;

            if (r > 0.40f) {

            } else {
                player->winnings = 1.0f;
                
                cout << "He beat you up.." << endl;
                WaitMs(1000);

                cout << "Took all your money.." << endl;
                WaitMs(1000);

                cout << "And left." << endl;
                WaitMs(2000);

                cout << "Oh hey, he left a dollar." << endl;
                WaitMs(1000);

                cout << "New Balance: 1.00$\n" << endl;
                cout << ":(  <-  you" << endl;
            }
        }

        WaitInp("press enter..");
        return;
    }
}