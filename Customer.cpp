#include <string>
using namespace std;

class Customer {
    int id;
    string name;
    string phone;
public:
    Customer(int id, string name, string phone) : id(id), name(name), phone(phone) {}
    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
};
