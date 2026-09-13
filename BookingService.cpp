#include <iostream>
#include <vector>
using namespace std;

class BookingService {
    PriceCalculator calculator;
    TicketPrinter printer;
public:
    Booking* book(Customer* customer, Show* show, const vector<int>& seatNumbers, Payment& payment) {
        if (!customer || !show || seatNumbers.empty()) return nullptr;

        vector<ShowSeat*> selected;
        for (int number : seatNumbers) {
            for (ShowSeat* existing : selected)
                if (existing->getNumber() == number) return nullptr;

            ShowSeat* seat = show->findSeat(number);
            if (!seat || !seat->isAvailable()) return nullptr;
            selected.push_back(seat);
        }

        double total = calculator.calculate(selected);
        for (ShowSeat* seat : selected) seat->book();

        if (!payment.pay(total)) {
            for (ShowSeat* seat : selected) seat->release();
            cout << "Payment failed. Booking was not confirmed.\n";
            return nullptr;
        }

        Booking* booking = new Booking(customer, show, selected, total);
        printer.print(*booking, payment.method());
        return booking;
    }

    bool cancel(Booking* booking) {
        if (!booking || booking->getStatus() != "CONFIRMED") return false;
        for (ShowSeat* seat : booking->getSeats()) seat->release();
        booking->cancel();
        return true;
    }

    void printTicket(const Booking* booking, const string& paymentMethod) const {
        if (booking) printer.print(*booking, paymentMethod);
    }
};
