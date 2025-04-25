#pragma once
#include "InterestDecorator.h"
#include <iostream>
using namespace std;

class SavingInterestDecorator : public InterestDecorator
{
public:
    static double MONTHLY_INTEREST; // 2% Monthly Interest
    SavingInterestDecorator(Account* acc);
    void applyInterest() override; // apply interest monthly
};