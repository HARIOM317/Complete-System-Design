#include <iostream>

using namespace std;

// _____ Subsystem _____
class FlightBooking
{
public:
    void bookFlight()
    {
        cout << "Flight Booked!\n";
    }
};

class HotelBooking
{
public:
    void bookHotel()
    {
        cout << "Hotel Booked!\n";
    }
};

class paymentGateway
{
public:
    void makePayment()
    {
        cout << "Payment Successful!\n";
    }
};

// _____ Facade _____
class TravelFacade
{
private:
    FlightBooking flight;
    HotelBooking hotel;
    paymentGateway payment;

public:
    void bookCompleteTrip()
    {
        flight.bookFlight();
        hotel.bookHotel();
        payment.makePayment();
        cout << "Your trip is booked successfully!\n";
    }
};

// Client
int main()
{
    TravelFacade travel;
    travel.bookCompleteTrip();

    return 0;
}