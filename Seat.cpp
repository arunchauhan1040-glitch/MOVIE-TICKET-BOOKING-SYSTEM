#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

enum class SeatStatus { AVAILABLE, BOOKED };

class Seat {
    int number;
    SeatType type;
public:
    Seat(int number, SeatType type) : number(number), type(type) {}
    int getNumber() const { return number; }
    SeatType getType() const { return type; }
    string typeName() const {
        switch (type) {
            case SeatType::SILVER: return "SILVER";
            case SeatType::GOLD: return "GOLD";
            default: return "PLATINUM";
        }
    }
};
