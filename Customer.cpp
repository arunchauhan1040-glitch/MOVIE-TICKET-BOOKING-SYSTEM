#include <string>
using namespace std;

class Customer {
    int id;
    string name;
    string phone;
public:
    Customer(int id, string name, string phone) {
        this->id = id;
        this->name = name;
        this->phone = phone;
    }
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
};
