#include "GIC100DayDecorator.h"
#include "History.h"
#include "Utilities.h"

double GIC100DayDecorator::HUNDRED_DAYS_INTEREST = 0.05;

GIC100DayDecorator::GIC100DayDecorator(Account* acc)
    : InterestDecorator(acc)
{}

void GIC100DayDecorator::applyInterest()
{
    // Calculate how many times 100 days has passed
    int hundredDaysPassed = Utilities::getDaysBetween(History::getLastInterestDate(decoratedAccount->getAccountNumber()), Utilities::getTodayString()) / 100;

    if (hundredDaysPassed > 0)
    {
        double interest = decoratedAccount->getBalance() * HUNDRED_DAYS_INTEREST * hundredDaysPassed;
        
        cout << "\nFixed Deposit Account Interest Applied: +" << interest << endl;
        decoratedAccount->depositInterest(interest);
    }
    else
    {
        cout << "\nNot enough days to apply interest" << endl;
    }
}