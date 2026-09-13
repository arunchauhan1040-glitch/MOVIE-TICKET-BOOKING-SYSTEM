#include <vector>
#include <string>
using namespace std;

class Show {
    int id;
    Movie* movie;   // Aggregation: Movie exists independently of a Show.
    Screen* screen; // Association with a screen.
    string startTime;
    vector<ShowSeat> showSeats; // Composition: a show owns its seat states.
public:
    Show(int id, Movie* movie, Screen* screen, string startTime)
        : id(id), movie(movie), screen(screen), startTime(startTime) {
        for (Seat& seat : screen->getSeats()) showSeats.emplace_back(&seat);
    }
    int getId() const { return id; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }
    const vector<ShowSeat>& getShowSeats() const { return showSeats; }
    ShowSeat* findSeat(int number) {
        for (auto& s : showSeats) if (s.getNumber() == number) return &s;
        return nullptr;
    }
};
