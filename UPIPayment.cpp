#include <iostream>
#include <string>
using namespace std;

class UPIPayment : public Payment {
    string upiId;
public:
    explicit UPIPayment(string upiId) : upiId(upiId) {}
    bool pay(double amount) override {
        if (amount <= 0 || upiId.find('@') == string::npos) return false;
        cout << "UPI payment successful: Rs." << amount << "\n";
        return true;
    }
    string method() const override { return "UPI"; }
};
