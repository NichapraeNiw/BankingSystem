#pragma once
#include "InterestDecorator.h"
#include <iostream>
using namespace std;

class GIC12MonthDecorator : public InterestDecorator
{
public:
    static double YEARLY_INTEREST; // 7% interest
    GIC12MonthDecorator(Account* acc);

    void applyInterest() override; // apply interest every year
};