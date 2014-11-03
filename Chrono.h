namespace Chrono {
    
    using namespace std;
    enum class Month {
        Jan = 1,
        Feb,
        Mar,
        Apr,
        May,
        Jun,
        Jul,
        Aug,
        Sep,
        Oct,
        Nov,
        Dec
    };
    
    class Date {
    public:
        class Invalid {}; // to throw as exception
        
        Date(int y, Month m, int d); // check for valid date and initialize
        Date(); // default constructor
        // the default copy operations are fine
        
        // nonmodifying operations
        int day() const {return d;}
        Month month() const {return m;}
        int year() const {return y;}
        
        // modifying operations
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
        
        //friend ostream& operator<<(ostream& os, const Date& d);
    private:
        int y;
        Month m;
        int d;
        
    };
    
    bool leapyear(int y); // true if year is a leap year
    bool is_date(int y, Month m, int d);
    
    long date_to_days(const Date& d);
    Date days_to_date(long g);
    
    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);
    
    ostream& operator<<(ostream& os, const Date& d);
    
    istream& operator>>(istream& is, Date& dd);
    
} // Chrono