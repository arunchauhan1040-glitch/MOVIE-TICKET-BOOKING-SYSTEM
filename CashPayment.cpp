#include <iostream>
using namespace std;

class CashPayment : public Payment {
    double cashReceived;
public:
    explicit CashPayment(double cashReceived) : cashReceived(cashReceived) {}
    bool pay(double amount) override {
        if (amount <= 0 || cashReceived < amount) return false;
        cout << "Cash payment successful. Change: Rs." << cashReceived - amount << "\n";
        return true;
    }
    string method() const override { return "CASH"; }
};
