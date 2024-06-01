#pragma once

// Clears the terminal
void ClearScreen ();
// Waits for ms number of milliseconds
void WaitMs (int ms);
// Waits for user input [ENTER] then returns
void WaitInp (std::string msg);
// Get one character as input
char GetChar ();
// Linear interp to a number
void ShowRollLinear (float roll);
// Show the roll
void ShowRoll (float roll);
// Crawl i to x
float Crawl (float i, const float x, const float m = 0.01f);