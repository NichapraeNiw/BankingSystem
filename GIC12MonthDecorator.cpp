#include "GIC12MonthDecorator.h"
#include "History.h"
#include "Utilities.h"
#include <ctime>

double GIC12MonthDecorator::YEARLY_INTEREST = 0.07;


GIC12MonthDecorator::GIC12MonthDecorator(Account* acc)
	: InterestDecorator(acc)
{}


void GIC12MonthDecorator::applyInterest()
{
    tm lastInterest = Utilities::stringToDate(History::getLastInterestDate(decoratedAccount->getAccountNumber()));
    tm today = Utilities::stringToDate(Utilities::getTodayString());

    // Calculate the difference in months
    int yearDiff = today.tm_year - lastInterest.tm_year;
    if (yearDiff > 0)
    {
        double interest = decoratedAccount->getBalance() * YEARLY_INTEREST * yearDiff; // 7% After 1 Year
        
        cout << "\nTFSA (12 Months) Interest Applied: +" << interest << endl;
        decoratedAccount->depositInterest(interest);
    }
    else
    {
        cout << "\nNot enough years to apply interest" << endl;
    }
}
