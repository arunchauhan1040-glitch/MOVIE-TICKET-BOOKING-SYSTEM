#include <string>
using namespace std;

class Movie {
    int id;
    string title, language;
    int durationMinutes;
public:
    Movie() : id(0), title(""), language(""), durationMinutes(0) {}
    Movie(int id, string title, string language, int durationMinutes)
        : id(id), title(title), language(language), durationMinutes(durationMinutes) {}
    // Compile-time polymorphism through constructor overloading.
    Movie(int id, string title) : id(id), title(title), language("English"), durationMinutes(120) {}
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return durationMinutes; }
};
