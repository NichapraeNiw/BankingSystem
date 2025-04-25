#pragma once
#include "InterestDecorator.h"
#include <iostream>
using namespace std;

class GIC100DayDecorator : public InterestDecorator
{
public:
    static double HUNDRED_DAYS_INTEREST; // 5% interest rate
    GIC100DayDecorator(Account* acc);

    void applyInterest() override; // apply interest rate every 100 days
};