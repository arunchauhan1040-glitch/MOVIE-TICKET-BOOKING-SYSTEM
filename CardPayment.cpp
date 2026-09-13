#include <iostream>
#include <string>
using namespace std;

class CardPayment : public Payment {
    string cardNumber;
public:
    explicit CardPayment(string cardNumber) : cardNumber(cardNumber) {}
    bool pay(double amount) override {
        if (amount <= 0 || cardNumber.size() != 16) return false;
        for (char c : cardNumber) if (c < '0' || c > '9') return false;
        cout << "Card payment successful: Rs." << amount << "\n";
        return true;
    }
    string method() const override { return "CARD"; }
};
