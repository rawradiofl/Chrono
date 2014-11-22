

#include <iostream>
#include "Chrono.h"


int main(int argc, const char * argv[]) {
    Chrono::Date today{2014, Chrono::Month::Oct, 30};
    long days = Chrono::date_to_days(today);
    Chrono::Date today2 = Chrono::days_to_date(days);
    std::cout << "Hello, World!\n" << "Date in days: " << days << std::endl;
    std::cout << today << std::endl;
    std::cout << today2 << std::endl;
    return 0;
}
