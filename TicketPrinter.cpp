#include <iostream>
using namespace std;

class TicketPrinter {
public:
    void print(const Booking& booking, const string& paymentMethod) const {
        cout << "\n========== MOVIE TICKET ==========\n";
        cout << "Booking ID : " << booking.getId() << "\n";
        cout << "Customer   : " << booking.getCustomer()->getName() << "\n";
        cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        cout << "Language   : " << booking.getShow()->getMovie()->getLanguage() << "\n";
        cout << "Screen     : " << booking.getShow()->getScreen()->getName() << "\n";
        cout << "Show Time  : " << booking.getShow()->getStartTime() << "\n";
        cout << "Seats      : ";
        for (ShowSeat* seat : booking.getSeats()) cout << seat->getNumber() << "(" << seat->typeName() << ") ";
        cout << "\nAmount     : Rs." << booking.getTotal() << "\n";
        cout << "Payment    : " << paymentMethod << "\n";
        cout << "Status     : " << booking.getStatus() << "\n";
        cout << "==================================\n";
    }
};
