#include <vector>
#include <string>
using namespace std;

class Screen {
    int id;
    string name;
    vector<Seat> seats;
public:
    Screen(int id, string name, int silver, int gold, int platinum) : id(id), name(name) {
        int n = 1;
        for (int i = 0; i < silver; ++i) seats.emplace_back(n++, SeatType::SILVER);
        for (int i = 0; i < gold; ++i) seats.emplace_back(n++, SeatType::GOLD);
        for (int i = 0; i < platinum; ++i) seats.emplace_back(n++, SeatType::PLATINUM);
    }
    int getId() const { return id; }
    string getName() const { return name; }
    vector<Seat>& getSeats() { return seats; }
    const vector<Seat>& getSeats() const { return seats; }
};
