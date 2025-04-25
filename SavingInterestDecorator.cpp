#include "SavingInterestDecorator.h"
#include "History.h"
#include "Utilities.h"
#include <ctime>

double SavingInterestDecorator::MONTHLY_INTEREST = 0.02;

SavingInterestDecorator::SavingInterestDecorator(Account* acc)
	: InterestDecorator(acc) 
{}

void SavingInterestDecorator::applyInterest()
{
    tm lastInterest = Utilities::stringToDate(History::getLastInterestDate(decoratedAccount->getAccountNumber()));
    tm today = Utilities::stringToDate(Utilities::getTodayString());

    // Calculate the difference in months
    int yearDiff = today.tm_year - lastInterest.tm_year;
    int monthDiff = today.tm_mon - lastInterest.tm_mon;

    int totalMonths = yearDiff * 12 + monthDiff;

    if (totalMonths > 0)
    {
        double interest = decoratedAccount->getBalance() * MONTHLY_INTEREST * totalMonths;
        
        cout << "\nSaving Account Interest Applied: +" << interest << endl;
        decoratedAccount->depositInterest(interest);
    }
    else
    {
        cout << "\nNot enough months to apply interest" << endl;
    }
}