#include <vector>
#include <string>
using namespace std;

class Booking {
    static int nextBookingId;
    int id;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    double total;
    string status;
public:
    Booking(Customer* customer, Show* show, const vector<ShowSeat*>& seats, double total)
        : id(nextBookingId++), customer(customer), show(show), seats(seats), total(total), status("CONFIRMED") {}
    static int getNextBookingId() { return nextBookingId; }
    int getId() const { return id; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getTotal() const { return total; }
    string getStatus() const { return status; }
    void cancel() { status = "CANCELLED"; }
};

int Booking::nextBookingId = 1001;
