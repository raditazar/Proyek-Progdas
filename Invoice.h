#ifndef INVOICE_H
#define INVOICE_H
using namespace std;
#include "Customer.h"
#include "Car.h"
#include "Payment.h"

class Invoice{
    private:
        string invoiceNumber;
        Customer* customer;
        Car* rentedCar;
        int days;
        Payment payment;
        double total;
        int i = 1;
    public:
        Invoice(Customer* cus, Car* car, int days):
            customer(cus), rentedCar(car), days (days),
            payment(Payment("", 0)), total(car->getPrice() * days){
                invoiceNumber = "INV" + to_string(i++);
            }
        void choosePayment(){
            int choice;
            string method;
            cout << "Choose payment method: "
                << "\n1. Credit Card"
                << "\n2. Debit Card"
                << "\n3. Digital Wallet"
                << "\nChoose a payment: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    method = "Credit Card";
                    break;
                case 2:
                    method = "Debit Card";
                    break;
                case 3:
                    method = "Digital Wallet";
                    break;
                default:
                    method = "Please choose the correct number.";
            }
            payment = Payment(method, total);
        }

        void printInvoice(){
            cout << "Invoice Number: " << invoiceNumber << endl;
            cout << "Customer: " << customer->getUsername() << endl;
            cout << "Car: " << rentedCar->getBrand() << " " << rentedCar->getModel() << endl;
            cout << "Rental Days: " << days << endl;
            cout << "Total Cost: Rp" << total << endl;
            cout << "Payment Method: " << payment.getPaymentMethod() << endl;
            cout << "Payment Status: " << (payment.getPaymentStatus() ? "Paid" : "Pending") << endl;
        }

};
#endif