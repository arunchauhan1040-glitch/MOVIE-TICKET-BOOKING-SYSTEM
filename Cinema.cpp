#include <vector>
#include <string>
using namespace std;

class Cinema {
    int id;
    string name;
    vector<Screen> screens; // Composition: Cinema owns its screens.
public:
    Cinema(int id, string name) : id(id), name(name) {}
    void addScreen(const Screen& screen) { screens.push_back(screen); }
    int getId() const { return id; }
    string getName() const { return name; }
    vector<Screen>& getScreens() { return screens; }
    const vector<Screen>& getScreens() const { return screens; }
};
