#include <iostream>
#include <iomanip>
#include <fstream>
#include "Player.h"
#include "Cases.h"
#include "InventorySystem.h"

#define OUT_SAVE "./Saves/save"
#define OUT_RECS "./Saves/highscore"
#define RAGE_MSG "You rage quit lol"

using namespace std;

void Load (Player& player) {
    ifstream inputs(OUT_SAVE);
    ifstream records(OUT_RECS);

    if (!inputs.is_open() || !records.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }
    
    string w;
    std::getline(inputs, w);
    inputs.close();

    istringstream iss(w);

    if (w == RAGE_MSG || w == "") return;

    // Load values from save file
    string p_winnings, p_luck, p_day, p_flags, i_case, highscore;
    iss >> p_winnings >> p_luck >> p_day >> p_flags;
    std::getline(records, highscore);

    // Put into player object
    player.highscore = stof(highscore);
    player.day = stoi(p_day);
    player.winnings = stof(p_winnings);
    player.luck = stof(p_luck);
    player.event_flags = stoi(p_flags);

    // Load inventory seperately
    auto cd = CaseDistribution::Instance();

    for (int i = 0; i < CaseDistribution::NUM_OF_CASES; ++i) {
        iss >> i_case;
        int n_case = stoi(i_case);
        
        if (n_case == -1) continue;
        
        if (n_case == -2) {
            cout << "Missing Case" << endl;
            exit(0);
        }

        player.inventory.InsertCase(cd.cases[n_case]);
    }
}

int SlotToNumber (Slot& S) {
    auto cd = CaseDistribution::Instance();

    if (S.empty) return -1;

    for (int i = 0; i <= CaseDistribution::NUM_OF_CASES; ++i) {
        if (S.Scase.case_name == cd.cases[i].case_name) return i;
    }

    return -2;
}

void Save (Player& player) {
    cout << "Saving.." << endl;

    ofstream outputs(OUT_SAVE);
    ofstream records(OUT_RECS);

    if (!outputs.is_open() || !records.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }
    
    // Save into OUT_SAVE
    outputs << 
        player.winnings << " " << 
        player.luck << " " << 
        player.day << " " << 
        static_cast<int>(player.event_flags) << " ";

    for (auto S : player.inventory.slots) {
        outputs << SlotToNumber(S) << " ";
    }

    // Save highscore
    records << player.highscore;

    outputs.close();
    records.close();
}

void Rage () {
    ofstream outputs(OUT_SAVE);

    if (!outputs.is_open()) { 
        cerr << "Error opening the file!" << endl;
        exit(1);
    }
    
    outputs << RAGE_MSG;
    outputs.close();
}