#include <iostream>
#include <string>
#include "Generators.h"
#include "Cases.h"

using namespace std;

Case::Case () {}

Case::Case (string _name, float _threshold, float _price, float _multiplier) {
    money_potential = _price * _multiplier;
    
    case_name = _name;
    threshold = _threshold;
    price = _price;
    multiplier = _multiplier;
}

void Case::Print () {
    printf("[ %-13s | Roll: %6.2f | Potential: x%4.2f | Price: %6.2f$ ]\n",
        case_name.c_str(),
        threshold,
        multiplier,
        price);
}

CaseDistribution& CaseDistribution::Instance () {
    static CaseDistribution caseDist;
    return caseDist;
}

CaseDistribution::CaseDistribution() {}

Case CaseDistribution::CollectCase () {
    return Instance().cases[gen::random(0, 3)];
}