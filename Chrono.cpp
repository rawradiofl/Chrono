#include <iostream>
#include "Chrono.h"
using namespace std;

namespace Chrono {

    Date::Date(int yy, Month mm, int dd)
        :y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy,mm,dd)) throw Invalid{};
    }

    const Date& default_date()
    {
        static Date dd {2001, Month::Jan, 1};
        return dd;
    }

    Date::Date()
        :y{default_date().year()},
         m{default_date().month()},
         d{default_date().day()}
    {

    }

    void Date::add_day(int n)
    {
        Date tmp = Date(y, m, d);
        long days = date_to_days(tmp);
        days += n;
        tmp = days_to_date(days);
        y = tmp.y;
        m = tmp.m;
        d = tmp.d;
    }

    //void Date::add_month(int n)
    //{

    //}

    void Date::add_year(int n)
    {
        if (m == Month::Feb && d == 29 && !leapyear(y+n)) {
            m = Month::Mar; // use march 1 instead of Feb 29
            d = 1;
        }
        y+=n;
    }

    // helper functions

    bool is_date(int y, Month m, int d)
    {
        // assume y is valid
        if (d <= 0) return false;
        if (m < Month::Jan || Month::Dec < m) return false;

        int days_in_month = 31; // most months have 31 days

        switch (m) {
        case Month::Feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Month::Apr: case Month::Jun: case Month::Sep: case Month::Nov:
            days_in_month = 30;
            break;
        default:
            break;
        }

        if (days_in_month < d) return false;

        return true;
    }

    bool leapyear(int y)
    {
        if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
            return true;
        else
            return false;
    }

    bool operator==(const Date& a, const Date& b)
    {
        return a.year() == b.year()
            && a.month() == b.month()
            && a.day() == b.day();
    }

    bool operator!=(const Date& a, const Date& b)
    {
        return !(a==b);
    }

    long date_to_days(const Date& d)
    {
        long month = int(d.month());
        long y = d.year();
        month = (month + 9) % 12;
        y = y - month/10;
        return 365*y + y/4 - y/100 + y/400 + (month*306 + 5)/10 + ( d.day() - 1 );
    }

    Date days_to_date(long g)
    {
        long mi, mm, ddd = 0;
        int y, dd = 0;
        y = static_cast<int>((10000*g + 14780)/3652425);
        ddd = g - (365*y + y/4 - y/100 + y/400);
        if (ddd < 0) {
            y = y - 1;
            ddd = g - (365*y + y/4 - y/100 + y/400);
        }
        mi = (100*ddd + 52)/3060;
        mm = (mi + 2)%12 + 1;
        y = static_cast<int>(y + (mi + 2)/12);
        dd = static_cast<int>(ddd - (mi*306 + 5)/10 + 1);
        Month m = static_cast<Month>(mm);

        return Date(y, m, dd);
    }

    ostream& operator<<(ostream& os, const Date& d)
    {
        os << '('<< d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
        return os;
    }

    istream& operator>>(istream& is, Date& dd)
    {
        int y,m,d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is) return is;

        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // oops. formatting error
            is.clear(ios_base::failbit);
            return is;
        }

        dd = Date(y, Month(m), d);

        return is;
    }

    int n = int(Month::Jan);
}
