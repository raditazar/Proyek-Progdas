#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>
using namespace std;

class Car{
    private:
    string brand;
    string model;
    double price;
    bool isAvailable;

    public:
    Car(string brand, string model, double price, bool isAvailable){
        this->brand = brand;
        this->model = model;
        this->price = price;
        this->isAvailable = isAvailable;
    }
    string getBrand()const{
        return brand;
    }
    string getModel()const{
        return model;
    }
    double getPrice()const{
        return price ;
    }
    bool getAvailability()const{
        return isAvailable;
    }

    void setAvailability(bool newStatus){
        isAvailable = newStatus;
    }
    void display()const{
        cout << "Model: " << model << "\nBrand: " << brand
             << "\nPrice per day: Rp" << price << "\nAvailable: " << (isAvailable? "Yes" : "No") << endl; 
    }
};
#endif