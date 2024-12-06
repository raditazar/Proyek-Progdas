#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <vector>
class Customer: public User{
    public: 
        Customer(string username, string password) : User(username, password){}
        
        void addBooking(const string& booking){
            bookings.push_back(booking);
        }

        const vector<string>& getBookings() const{
            return bookings;
        }
    private:
        vector<string> bookings;

};
#endif