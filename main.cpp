/*************************************************
Aufgabe Nr./Task No.: H5
Nachname/Last,Family Name: Abaza
Vorname/First,Given Name: Ahmed
Matrikelnummer/Matriculation number: 3035482
Uni-Email: ahmed.abaza@stud.uni-due.de
Studiengang/Course of Studies: ISE CE
*************************************************/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Date
{
private:
    short unsigned int day, month, year;
public:
    Date()
    {
        day = 01;
        month = 01;
        year = 1970;
    };
    Date(short unsigned int d, short unsigned int m, short unsigned int y)
    {
        day = d;
        month = m;
        year = y;
    };
    Date operator+(short unsigned int n)
    {
        const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        Date sum;
        unsigned int lengthOfMonth = daysInMonth[month - 1];
        unsigned int carry;
            if(month == 12)
            {
                sum.day = day + n;
                sum.month = month;
                sum.year = year;
                if(sum.day > 31)
                {
                    carry = 31 - day;
                    sum.day = n - carry;
                    sum.month = 1;
                    sum.year = year + 1;
                }
            }
            else
            {
                sum.day = day + n;
                sum.month = month;
                sum.year = year;
                if(sum.day > lengthOfMonth)
                {
                    carry = lengthOfMonth - day;
                    sum.day = n - carry;
                    sum.month = month +1;
                    sum.year = year;
                }
            }
        return sum;
    };

    friend istream& operator>>(istream& in, Date& z)
    {
        short unsigned int dd, mm, yy;
        char c;
        in >> dd >> c >> mm >> c >> yy;
        z.day = dd;
        z.month = mm;
        z.year = yy;
        return in;
    };

    friend ostream& operator<<(ostream &out, Date y)
    {
        short unsigned int dd, mm, yy;
        dd = y.day;
        mm = y.month;
        yy = y.year;
        out << setfill('0') << setw(2) << dd << '.' << setfill('0') << setw(2) << mm << '.' << yy;
        return out;
    }

};

enum Board {nomeals, breakfast, halfpension, allinclusive};
//ostream& operator<<(ostream &out, board y)

class Hotel
{
private:
    string name;
    Date arrival;
    short unsigned int nights, singles, doubles;
    Board board;
    float priceNightSingle, priceNightDouble;
    bool parking;
public:
    Hotel()
    {
        char c, p;
        cout << "Name of hotel: ";
        cin.sync();
        getline(cin, name);
        cout << "Arrival on: ";
        cin >> arrival;
        cout << "Number of nights: ";
        cin >> nights;
        if(nights > 28)
        {
            cerr << "Maximum number of nights is 28 night!" << endl;
            nights = 28;
            cout << "Number of nights automatically set to 28 night." << endl;
        }
        cout << "Number of single bed rooms: ";
        cin >> singles;
        cout << "Number of double bed rooms: ";
        cin >> doubles;
        cout << "a all inclusive" << endl
             << "b breakfast" << endl
             << "h half board" << endl
             << "w without meals" << endl;
        cin >> c;
        if(c == 'a')
            board = allinclusive;
        if(c == 'b')
            board = breakfast;
        if(c == 'h')
            board = halfpension;
        if(c == 'w')
            board = nomeals;
        cout << "price one night in a single bed room: ";
        cin >> priceNightSingle;
        cout << "price one night in a double bed room: ";
        cin >> priceNightDouble;
        cout << "with parking (y(es) or n(o)): ";
        cin >> p;
        if(p == 'y')
            parking = true;
        if(p == 'n')
            parking = false;
    };

    ~Hotel()
    {
        unsigned int guestsNo = singles + (doubles * 2);
        cout << "destructor hotel " << name << " at " << arrival << " for " << guestsNo << " guests done." << endl;
    };

    float get_price()
    {
        float sum;
        sum = nights * ((singles * priceNightSingle) + (doubles * priceNightDouble));
        if(parking == true)
        {
            sum = sum + (nights * 10);
        }
        return sum;
    };

    Date get_arrival()
    {
        return arrival;
    };

    Date get_checkout()
    {
        Date departure;
        departure = arrival + nights;
        return departure;
    }

    unsigned int get_guests()
    {
        unsigned int guestsNo = singles + (doubles * 2);
        return guestsNo;
    };

    void print()
    {
        cout <<'\t'<< "hotel " << arrival <<" "<<name<< " for " << nights<< " night(s) ";
        if(singles > 0)
            cout << singles << " single bed room(s) ";
        if(doubles > 0)
            cout << doubles << " double bed room(s) ";
        cout << "with "<<endl;
        if(board == 0)
        {
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t'<<" ";
            cout << "no meals";
        }
        if(board == 1)
        {
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t'<<" ";
            cout << "breakfast";
        }
        if(board == 2)
        {
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t'<<" ";
            cout << "half board";
        }
        if(board == 3)
        {
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t';
            cout <<'\t'<<" ";
            cout << "all inclusive";
        }
        if(parking == true)
            cout << ", parking included";
    }
};

class Transport
{
public:
    virtual ~Transport()
    {
        cout << "destructor transport done" << endl;
    };
    virtual bool withTransfer() = 0;
    virtual float get_price() = 0;
    virtual void print() = 0;
};


class SelfOrganised : public Transport
{
public:
    SelfOrganised(){};
    virtual ~SelfOrganised()
    {
        cout << "destructor SelfOrganised done." << endl;
    };
    virtual bool withTransfer()
    {
        return false;
    };
    virtual float get_price()
    {
        float x = 0.00;
        return x;
    };
    virtual void print()
    {
        cout << "self organised transport." << endl;
    };
};

class PublicTransport : public Transport
{
private:
    Date departure;
    string code, from, to;
    float priceOneSeat;
    bool firstClass;
public:
    PublicTransport(Date d, string c, string f, string t, float p, bool fc = false)
    {
        departure = d;
        code = c;
        from = f;
        to = t;
        priceOneSeat = p;
        firstClass = fc;
    }
    virtual ~PublicTransport()
    {
        cout << "destructor Public transport " << code << " at " << departure << " done" << endl;
    }
    virtual void print()
    {
        cout << code << " at " << departure << " from " << from << " to " << to;
        if(firstClass == true)
        {
            cout << "first class";
        }
        cout << endl;
    }
    virtual float get_price()
    {
        return priceOneSeat;
    }
    virtual bool get_class()
    {
        return firstClass;
    }
};

class Flight : public PublicTransport
{
private:
    bool transfer;
public:
    Flight(Date d, string c, string f, string t, float p, bool fc = false, bool tr = true): PublicTransport(d, c, f, t, p, fc)
    {
        transfer = tr;
    }
    virtual ~Flight()
    {
        cout << "destructor flight done." << endl;
    }
    virtual bool withTransfer()
    {
        return transfer;
    }
    virtual float get_price()
    {
        float price = PublicTransport::get_price();
        bool classT = get_class();
        if(classT == true)
            price = 2 * price;
        return price;
    }
    virtual void print()
    {
        cout << "flight ";
        PublicTransport::print();
    }
};

class Train : public PublicTransport
{
public:
    Train(Date d, string c, string f, string t, float p, bool fc = false) : PublicTransport(d, c, f, t, p, fc){}
    virtual ~Train()
    {
        cout << "destructor train done" << endl;
    }
    virtual bool withTransfer()
    {
        return false;
    }
    virtual float get_price()
    {
        float price = PublicTransport::get_price();
        bool classT = get_class();
        if(classT == true)
            price = 1.5 * price;
        return price;
    }
    virtual void print()
    {
        cout << "train ";
        PublicTransport::print();
    }
};

class Trip
{
private:
    const unsigned int no;
    static unsigned int lastNo;
    unsigned int travellers;
    Hotel* hotel;
    Transport* transportOutward;
    Transport* transportBack;
    Trip* next;
public:
    Trip(unsigned int tr, Hotel *h, Transport *tro, Transport *trb, Trip *n = nullptr) : no(++lastNo)
    {
        travellers = tr;
        hotel = h;
        transportOutward = tro;
        transportBack = trb;
        next = n;
    }
    virtual ~Trip()
    {
        delete hotel;
        delete transportOutward;
        delete transportBack;
        cout << "destructor Trip done" << endl;
    }
    unsigned int get_no()
    {
        return no;
    }
    Trip* get_next()
    {
        return next;
    }
    void set_next(Trip* n)
    {
        next = n;
    }
    float get_price()
    {
        float pH = hotel->get_price();
        float pO = transportOutward->get_price();
        float pB = transportBack->get_price();
        pO = pO * travellers;
        pB = pB * travellers;
        float Total = pB + pO + pH;
        return Total;
    }
    void print()
    {
        cout << "Trip inquiry " << no << " for " << travellers << " Person(s)" << endl;
        cout << "Check-in:" << '\t';
        hotel->print();
        cout << endl << "outward journey: " << '\t';
        transportOutward->print();
        cout << endl << "journey back: " << '\t' << '\t';
        transportBack->print();
        if(transportBack->withTransfer() == true || transportOutward->withTransfer() == true)
        {
            cout << endl << "Transfer Included" << endl;
        }
        else
        {
            cout << endl << "NO Transfer Included" << endl;
        }
        cout << '\t' << '\t' << " Total price: " << get_price() << " EUR" << endl << endl;
    }
};

unsigned int Trip::lastNo = 0;

class TravelAgency
{
private:
    Trip* trips;
public:
    TravelAgency()
    {
        trips = nullptr;
    }
    void add(Trip* t)
    {
        t->set_next(trips);
        trips = t;
    }
    void removee(Trip* t)
    {
        if (trips != nullptr)
        {
            if(trips == t)
            {
                Trip* toremove = trips;
                trips = trips->get_next();
                delete toremove;
            }
            else
            {
                Trip* iterator = trips->get_next();
                Trip* previous = trips;
                while (iterator != nullptr)
                {
                    if (iterator == t)
                    {
                        previous->set_next(iterator->get_next());
                        delete iterator;
                        return;
                    }
                    previous = iterator;
                    iterator = iterator->get_next();
                }
            }
        }
    }
    Trip *searchh(unsigned int n)
    {
        Trip* iterator = trips;
        Trip* found = nullptr;
        while (iterator != nullptr)// || iterator->get_no() != n)
        {
            if(iterator->get_no() == n)
            {
                found = iterator;
                iterator = iterator->get_next();
            }
            else
            {
                iterator = iterator->get_next();
            }
        }
        return found;
    }
    void printAllTrips()
    {
        if(trips == nullptr)
            cerr << "No Trips Found, Please add trips first!!" << endl;
        else
        {
            Trip* iterator = trips;
            while (iterator != nullptr)
            {
                iterator->print();
                iterator = iterator->get_next();
            }
        }
    }
};

int main()
{
    char choice, c1, c2, c3;
    unsigned int notra, key;
    Trip* found = nullptr;
    Transport* tro = nullptr;
    Transport* trb = nullptr;
    TravelAgency main;
    do
   {
      cout << "0 End" << endl
           << "1 New Trip" << endl
           << "2 Search Trip" << endl
           << "3 Show all offers" << endl
           << "Your choice >> ";
      cin >> choice;
      switch (choice)
      {
        case '0':   break;
        case '1':   {   Hotel *H = new Hotel();
                        notra = H->get_guests();
                        Date z;
                        string code, from, to;
                        float price;
                        cout << "please choose transport for outward journey:" << endl;
                        cout << "0 self organised" << endl
                        << "1 flight" << endl
                        << "2 train" << endl
                        << "Your choice >> ";
                        cin >> c1;
                        switch(c1)
                        {
                        case '0':
                            {
                                SelfOrganised *SlfOrg = new SelfOrganised();
                                tro = SlfOrg;
                                break;
                            }
                        case '1':
                            {
                            cout << "code of flight: ";
                            cin.sync();
                            getline(cin, code);
                            cout << "airport of departure: ";
                            cin.sync();
                            getline(cin, from);
                            cout << "airport of arrival: ";
                            cin.sync();
                            getline(cin, to);
                            cout << "price for one passenger: ";
                            cin >> price;
                            z = H->get_arrival();
                            Flight *fl = new Flight(z, code, from, to, price);
                            tro = fl;
                            break;
                            }
                        case '2':
                            cout << "code of train: ";
                            cin.sync();
                            getline(cin, code);
                            cout << "station of departure: ";
                            cin.sync();
                            getline(cin, from);
                            cout << "station of arrival: ";
                            cin.sync();
                            getline(cin, to);
                            cout << "price for one passenger: ";
                            cin >> price;
                            z = H->get_arrival();
                            Train *tr = new Train(z, code, from, to, price);
                            tro = tr;
                            break;
                        }
                        cout << "please choose transport for journey back:" << endl;
                        cout << "0 self organised" << endl
                        << "1 flight" << endl
                        << "2 train" << endl
                        << "Your choice >> ";
                        cin >> c2;
                        switch(c2)
                        {
                        case '0':
                            {
                                SelfOrganised *SlfOrgB = new SelfOrganised();
                                trb = SlfOrgB;
                                break;
                            }
                        case '1':
                            {
                            cout << "code of flight: ";
                            cin.sync();
                            getline(cin, code);
                            cout << "airport of departure: ";
                            cin.sync();
                            getline(cin, from);
                            cout << "airport of arrival: ";
                            cin.sync();
                            getline(cin, to);
                            cout << "price for one passenger: ";
                            cin >> price;
                            z = H->get_checkout();
                            Flight *flB = new Flight(z, code, from, to, price);
                            trb = flB;
                            break;
                            }
                        case '2':
                            cout << "code of train: ";
                            cin.sync();
                            getline(cin, code);
                            cout << "station of departure: ";
                            cin.sync();
                            getline(cin, from);
                            cout << "station of arrival: ";
                            cin.sync();
                            getline(cin, to);
                            cout << "price for one passenger: ";
                            cin >> price;
                            z = H->get_checkout();
                            Train *trB = new Train(z, code, from, to, price);
                            trb = trB;
                            break;
                        }
                    Trip *added = new Trip(notra, H, tro, trb);
                    main.add(added);
                    cout << "Trip added successfully!" << endl << endl;
                    break;
                    }
        case '2':   cout << "number of trip: ";
                    cin >> key;
                    found = main.searchh(key);
                    if(found == nullptr)
                    {
                        cout << "No trip found!" << endl;
                    }
                    else
                    {
                        found->print();
                        cout << endl << endl <<"(d)elete or (n)ot: ";
                        cin >> c3;
                        if(c3 == 'd')
                        {
                            main.removee(found);
                        }
                    }
                    break;
        case '3':   main.printAllTrips();
                    break;
        default:    cout << "sorry wrong choice" << endl;
      }
    } while(choice != '0');
    return 0;
}
