#pragma once

class Case {
    public:
    std::string case_name;
    float money_potential; // max winnings
    float threshold;       // least number for max winnings
    float price;           // case's price
    float multiplier;      // multiplied by price for money_potential

    Case ();
    Case (std::string _name, float _threshold, float _price, float _multiplier);

    void Print ();
};

class CaseDistribution {
    private:
    CaseDistribution();

    //                                    roll | price | multi
    Case wooden_case = Case("Wooden Case", 0.65f, 0.45f, 2.0f);      // cheap high risk case
    Case birch_case = Case("Birch Case", 0.5f, 0.6f, 2.0f);          // cheap medium risk case
    Case mahogany_case = Case("Mahogany Case", 0.35f, 0.6f, 1.7f);   // cheap low risk case
    Case iron_case = Case("Iron Case", 0.7f, 4.0f, 2.5f);            // medium high risk case
    Case golden_case = Case("Golden Case", 0.22f, 5.0f, 1.2f);       // medium low risk case
    Case diamond_case = Case("Diamond Case", 0.80f, 10.0f, 3.5f);    // expensive very high risk case
    Case elite_case = Case("Elite Case", 0.4f, 15.0f, 2.0f);         // expensive low risk case

    public:
    static CaseDistribution& Instance ();

    const static size_t NUM_OF_CASES = 6;
    
    Case cases[NUM_OF_CASES] = {
        wooden_case, birch_case, mahogany_case,
        iron_case, golden_case,
        diamond_case};

    Case elite_cases[1] = {elite_case};
    
    static Case CollectCase();
};