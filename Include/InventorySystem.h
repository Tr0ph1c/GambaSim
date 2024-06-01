#pragma once

#include "Cases.h"

class Slot {
    public:
    Case Scase;
    bool empty;

    Slot ();
};

class Inventory {
    public:
    const static int NUM_OF_SLOTS = 5;

    Slot slots[NUM_OF_SLOTS];
    
    Inventory();
    
    bool InsertCase (Case _case);

    void PrintInventory ();
};
