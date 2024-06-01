#pragma once

#include <vector>
#include <functional>
#include "Player.h"

class EventSystem {
    public:
    using Event = std::function<void(bool)>;
    static std::vector<Event> events;

    static Player* player;

    static void RunEvent ();
    static void InitEvents (Player* _player);


    static void GoodLuck (bool exit);
    static void FreeChest (bool exit);
    static void GuaranteedWin (bool exit);
    static void LowerAllIn (bool exit);

    static void BadLuck (bool exit);
    static void Robber (bool exit);
    static void HighRisk (bool exit);
    static void RollForYourLife (bool exit);

    static void ResetLuck (bool exit);
};
