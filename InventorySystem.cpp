#include <iostream>
#include <iomanip>
#include <string>
#include "Cases.h"
#include "CrossplatFuncs.h"
#include "InventorySystem.h"

using namespace std;

Slot::Slot () : empty(true) {}

Inventory::Inventory() {}

bool Inventory::InsertCase (Case _case) {
    for (int i = 0; i < NUM_OF_SLOTS; ++i) {
        if (slots[i].empty) {
            slots[i].Scase = _case;
            slots[i].empty = false;
            return true;
        }
    }

    return false;
}

void Inventory::PrintInventory () {
    for (int i = 0; i < NUM_OF_SLOTS; ++i) {
        Slot* s = &slots[i];
        cout << i << ") ";

        if (!s->empty) {
            s->Scase.Print();
        } else {
            cout << "[ EMPTY SLOT ]" << endl;
        }
    }
}
