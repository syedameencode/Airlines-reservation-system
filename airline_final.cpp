#include <iostream>
#include <string>
using namespace std;

// Template
template<class T>
T maxVal(T a, T b){ return a > b ? a : b; }

// Exception
class BookingError {
public:
    string msg;
    BookingError(string m){ msg = m; }
};

// Abstract class
class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a){ name = n; age = a; }
    Person(const Person &p){ name = p.name; age = p.age; }
    virtual void display() = 0;
};

// Single Inheritance
class Passenger : public Person {
public:
    string mobile, email;
    Passenger(string n, int a, string m, string e) : Person(n, a){
        mobile = m; email = e;
    }
    Passenger(const Passenger &p) : Person(p){
        mobile = p.mobile; email = p.email;
    }
    void display() override {
        cout << "Passenger: " << name << " | Age: " << age
             << " | Mobile: " << mobile << " | Email: " << email << endl;
    }
};

// Multilevel Inheritance
class Ticket : public Passenger {
public:
    string flight, seatType, date;
    double fare;
    Ticket(string n, int a, string m, string e, string f, string s, string d, double fr)
        : Passenger(n, a, m, e){
        flight = f; seatType = s; date = d; fare = fr;
    }
    void display() override {
        Passenger::display();
        cout << "Flight: " << flight << " | Seat: " << seatType
             << " | Date: " << date << " | Fare: Rs." << fare << endl;
    }
    // Method overloading
    void confirm(string info){ cout << "Booking confirmed for: " << info << endl; }
    void confirm(string info, double f){ cout << "Booking confirmed: " << info << " | Fare: Rs." << f << endl; }
};

int main(){
    string flights[3] = {"AI101 - Chennai to Delhi", "AI202 - Mumbai to Bangalore", "AI303 - Madurai to Hyderabad"};
    string dates[3]   = {"April 21", "April 22", "April 23"};
    double fares[2]   = {3500, 6500};

    string name, mobile, email;
    int age, fc, dc, sc;

    try {
        cout << "========== Airline Booking System ==========" << endl;
        cout << "Name: ";   cin >> name;
        cout << "Age: ";    cin >> age;
        cout << "Mobile: "; cin >> mobile;
        cout << "Email: ";  cin >> email;

        if(age <= 0) throw BookingError("Invalid age.");

        cout << "\n-- Available Flights --" << endl;
        for(int i = 0; i < 3; i++) cout << i+1 << ". " << flights[i] << endl;
        cout << "Choose flight (1-3): "; cin >> fc;
        if(fc < 1 || fc > 3) throw BookingError("Invalid flight choice.");

        cout << "\n-- Available Dates --" << endl;
        for(int i = 0; i < 3; i++) cout << i+1 << ". " << dates[i] << ", 2026" << endl;
        cout << "Choose date (1-3): "; cin >> dc;
        if(dc < 1 || dc > 3) throw BookingError("Invalid date choice.");

        cout << "\n-- Seat Class & Fare --" << endl;
        cout << "1. Economy  - Rs." << fares[0] << endl;
        cout << "2. Premium  - Rs." << fares[1] << endl;
        cout << "Choose (1-2): "; cin >> sc;
        if(sc < 1 || sc > 2) throw BookingError("Invalid seat choice.");

        string seat = (sc == 1) ? "Economy" : "Premium";
        string date = dates[dc-1] + ", 2026";

        Ticket t(name, age, mobile, email, flights[fc-1], seat, date, fares[sc-1]);
        Passenger p2 = t;  // copy constructor

        cout << "\n--- Booking Confirmed ---" << endl;
        t.display();
        t.confirm(name, fares[sc-1]);
        cout << "Higher fare ref: Rs." << maxVal(fares[0], fares[1]) << endl;

    } catch(BookingError e){
        cout << "Error: " << e.msg << endl;
    }

    return 0;
}