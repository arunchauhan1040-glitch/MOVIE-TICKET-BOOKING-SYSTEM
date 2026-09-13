#include <vector>
using namespace std;

class PriceCalculator {
public:
    double calculate(const ShowSeat& seat) const {
        switch (seat.getType()) {
            case SeatType::SILVER: return 150.0;
            case SeatType::GOLD: return 250.0;
            default: return 400.0;
        }
    }

    // Compile-time polymorphism through function overloading.
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0;
        for (ShowSeat* seat : seats) total += calculate(*seat);
        return total;
    }
};
