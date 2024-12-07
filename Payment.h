#ifndef PAYMENT_H
#define PAYMENT_H
using namespace std;
#include <string>
class Payment{
    private:
        string paymentMethod;
        double amount;
        bool isPaid;

    public:
        Payment(string method, double amount):
            paymentMethod(method), amount(amount), isPaid(true){}

        void processPayment(){
            isPaid = true;
        }
        
        string getPaymentMethod() const { return paymentMethod; }
        double getAmount() const { return amount; }
        bool getPaymentStatus() const { return isPaid; }
};
#endif