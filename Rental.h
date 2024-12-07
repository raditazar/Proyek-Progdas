#ifndef RENTAL_H
#define RENTAL_H

#include "Car.h"
#include "Customer.h"
#include "Admin.h"
#include "Invoice.h"
#include "Payment.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Rental{
    private:
    vector<Car> cars;
    vector<Car>rentedCars;
    vector<Customer> customers;
    vector<Admin> admins;
    Customer* currCus;
    Admin* currAdmin;

    public: 
    Rental() : currCus(nullptr), currAdmin(nullptr){
        loadAdminData();
        loadData();
        initializeAdmins();
        initializeCars();
    }

    void initializeAdmins(){
        if(admins.empty()){
            admins.push_back(Admin("Raditya", "radit123", true));
            saveAdminData();
        }
    }
    void saveAdminData(){
        ofstream adminFile("AdminData.txt");
        if(adminFile.is_open()){
            for(const auto& admin: admins){
                adminFile << admin.getUsername() << ", "
                          << admin.getPassword() << ", "
                          << (admin.getAdminStatus() ? "1" : "0")
                          <<endl;
            }
            adminFile.close();
        }
    }

    void loadAdminData() {
    ifstream adminFile("AdminData.txt");
    if(!adminFile) {
        return;
    }
    admins.clear();
    string line;
    while(getline(adminFile, line)) {
        stringstream ss(line);
        string username, password, isAdmin;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, isAdmin);

        // Hapus spasi di awal dan akhir
        username.erase(0, username.find_first_not_of(" "));
        username.erase(username.find_last_not_of(" ") + 1);
        
        password.erase(0, password.find_first_not_of(" "));
        password.erase(password.find_last_not_of(" ") + 1);
        
        isAdmin.erase(0, isAdmin.find_first_not_of(" "));
        isAdmin.erase(isAdmin.find_last_not_of(" ") + 1);

        bool isSuperAdmin = (isAdmin == "1");
        admins.push_back(Admin(username, password, isSuperAdmin));
    }
    adminFile.close();
}
    void initializeCars() {
        if (cars.empty()) {
            cars = {
                Car("Honda", "Civic", 35, true),
                Car("Toyota", "Avanza", 15, true),
                Car("Toyota", "Supra", 50, true)
            };
        }
    }
    
    void addNewAdmin(){
        if(!currAdmin || currAdmin->getAdminStatus() == false){
            cout << "Only super admin can add new admins!" << endl;
            return;
        }
        string username, password;
        char isSuperAdmin;
        bool isExist;
        do{
            isExist = false;
            cout << "Enter new admin username: ";
            cin >> username;
            for(const auto& admin : admins){
                if(admin.getUsername() == username){
                    cout << "Username already exist!" << endl;
                    isExist = true;
                    break;
                }
            }
        }while(isExist);
        cout << "Enter new admin password: ";
        cin >> password;
        cout << "Is new admin super admin? (y/n): ";
        cin >> isSuperAdmin;
        bool isSuper = (isSuperAdmin == 'y' || isSuperAdmin == 'Y');
        admins.push_back(Admin(username, password, isSuper));
        saveAdminData();
        cout << "Add new admin successfully." << endl;

    }
    void viewAllAdmins(){
        cout << "List Admin: " << endl;
        for (size_t i = 0; i < admins.size(); ++i) {
        cout << i + 1 << ". Username: " << admins[i].getUsername() 
             << " | Status: " << (admins[i].getAdminStatus() ? "Super Admin" : "Regular Admin") 
             << endl;
        }
    }

    void deleteAdmin() {
        if (!currAdmin || currAdmin->getAdminStatus() == false) {
            cout << "Hanya super admin yang dapat menghapus admin!" << endl;
            return;
        }
        viewAllAdmins();
        if (admins.size() <= 1) {
            cout << "Tidak dapat menghapus admin. Minimal harus ada satu admin." << endl;
            return;
        }
        int choice;
        cout << "Masukkan nomor admin yang akan dihapus: ";
        cin  >> choice;

        if (choice < 1 || choice > admins.size()) {
            cout << "Pilihan tidak valid!" << endl;
            return;
        }   

        if (&admins[choice - 1] == currAdmin) {
            cout << "Anda tidak dapat menghapus akun Anda sendiri!" << endl;
            return;
        }
        admins.erase(admins.begin() + (choice - 1));
        saveAdminData();
        cout << "Admin berhasil dihapus." << endl;
    }
    void confirmReturnCar(){
        if(!currAdmin){
            cout << "Not permitted"<< endl;
            return;
        }
        rentedCars.clear();
        for(auto& car : cars){
            if(!car.getAvailability()){
                car.display();
                rentedCars.push_back(car);
            }
        }
        if(rentedCars.empty()){
            cout << "There is no rented car." << endl;
            return;
        }
        string model;
        cout << "Masukkan mobil yang telah dikembalikan: ";
        cout << "\nModel: ";
        cin >> model;
        bool isReturned = false;
        for(auto& car: cars){
            if(car.getModel () == model && !car.getAvailability()){
                car.setAvailability(true);
                cout << model << "is returned." << endl;
                isReturned = true;
                return;
            }
        }
        if (!isReturned){
            cout << "Not found."<< endl;
        }

    }
    void adminMenu(){
        int choice;
        do{
            cout << "Admin Menu:" << endl;
            cout << "1. View all admins" << endl;
            cout << "2. Add new admin" << endl;
            cout << "3. Delete admin" << endl;
            cout << "4. Confirmation returned car" << endl;
            cout << "5. Back to main menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch(choice){
                case 1:
                    viewAllAdmins();
                    break;
                case 2: 
                    addNewAdmin();
                    break;
                case 3:
                    deleteAdmin();
                    break;
                case 4:
                    confirmReturnCar();
                    break;
            }
        }while(choice!= 5);
        
    }

    void signUp(){
        string username, password;
        bool isExist;
        do{
            isExist = false;
            cout << "Choose a username: ";
            cin >> username;
            
            for(const auto& customer: customers){
                if(customer.getUsername() == username){
                    cout << "Username already exists. Please choose another one." << endl;
                    isExist = true;
                    break;
                }
            }
        }while(isExist || username.empty());
        
        do{
            cout << "Choose a password: ";
            cin >> password;
        }while(password.empty());

        customers.push_back(Customer(username, password));
        cout << "Signed up successfully!" << endl;
        saveData();
    }

    Customer* login(){
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        for(auto& customer : customers){
            if(customer.getUsername() == username && customer.getPassword() == password){
                currCus = &customer;
                return currCus;
            }
        }
        cout << "Your username or password is incorrect" << endl;
        return nullptr;
    }

    Admin* adminLogin(){
        string username, password;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;
        for(auto& admin: admins){
            if(admin.getUsername() == username && admin.getPassword() == password){
                currAdmin = &admin;
                return currAdmin;
            }
        }
        cout << "Your username or password is incorrect."<< endl;
        return nullptr;
    }

    void addCar(const Car& car){
        cars.push_back(car);
    }

    void listAvailableCars() const {
        for(const auto& car : cars){
            if(car.getAvailability() == true){
                car.display();
            }
        }
    }

    void listNotAvailableCars(){
        rentedCars.clear();
        for(const auto& car : cars){
            if(car.getAvailability() == false){
                car.display();
                rentedCars.push_back(car);
            }
        }
    }
    
    bool bookCar(Customer& customer, const string& model, int days){
        for(auto& car : cars){
            if(car.getModel() == model && car.getAvailability() == true){
                Car* selected = &car;
                Invoice invoice(&customer, &car, days);
                invoice.choosePayment();
                car.setAvailability(false);
                string details = model + " for " + to_string(days) + " days.";
                customer.addBooking(details);
                invoice.printInvoice();
    
                saveData();
                return true;
            }
        }
        cout << "Car not available!" << endl;
        return false;
    }

    void displayMenu(){
        if(!currCus){
            cout << "Please log in first. \n";
            return;
        }
        int choice;
        do{
            cout << "----- Welcome to Car Rental -----\n"
                 << "1. List available cars\n"
                 << "2. Book a car\n"
                 << "3. View bookings\n"
                 << "4. Log out\n"
                 << "5. Exit\n"
                 << "Enter your choice: ";
            
            cin >> choice;
            switch(choice){
                case 1:
                    listAvailableCars();
                    break;
                case 2: {
                    string model;
                    int days;
                    cout << "Enter car model: ";
                    cin >> model;
                    cout << "Enter number of days: ";
                    cin >> days;
                    bookCar(*currCus, model, days);
                    break;
                }
                case 3: {
                    const auto& bookings = currCus->getBookings();
                    if(bookings.empty()){
                        cout << "No bookings found.\n";
                    }
                    else{
                        cout << "Bookings:\n";
                        for(size_t i = 0; i < bookings.size(); ++i){
                            cout << i + 1 << ". " << bookings[i] << endl;
                        }
                    }
                    break;
                }
                case 4:
                    currCus = nullptr;
                    return;
                case 5:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (true);
    }

    void saveData() {
    ofstream file("data.txt");
    if(file.is_open()) {
        for(const auto& customer : customers) {
            file << customer.getUsername() << ", " 
                 << customer.getPassword() << ", ";
            
            const auto& bookings = customer.getBookings();
            if(bookings.empty()) {
                file << "None";
            } else {
                for(size_t i = 0; i < bookings.size(); ++i) {
                    file << bookings[i];
                    if(i < bookings.size() - 1) {
                        file << "|";
                    }
                }
            }
            file << endl;
        }
        file.close();
    }

    ofstream carData("cars.txt");
    if(carData.is_open()) {
        for(const auto& car : cars) {
            carData << car.getBrand() << ", "
                    << car.getModel() << ", "
                    << car.getPrice() << ", "
                    << (car.getAvailability() ? "1" : "0") << endl;
        }
        carData.close();
    }
}

    void loadData() {
    ifstream file("data.txt");
    if(!file) return;
    customers.clear();
    string line;
    while(getline(file, line)) {
        istringstream ss(line);
        string username, password, bookingsStr;
        
        getline(ss, username, ',');
        username.erase(0, username.find_first_not_of(" "));
        username.erase(username.find_last_not_of(" ") + 1);
        
        getline(ss, password, ',');
        password.erase(0, password.find_first_not_of(" "));
        password.erase(password.find_last_not_of(" ") + 1);
        
        getline(ss, bookingsStr);
        bookingsStr.erase(0, bookingsStr.find_first_not_of(" "));
        bookingsStr.erase(bookingsStr.find_last_not_of(" ") + 1);

        Customer newCustomer(username, password);

        if(bookingsStr != "None") {
            istringstream bookingSs(bookingsStr);
            string booking;
            while(getline(bookingSs, booking, '|')) {
                newCustomer.addBooking(booking);
            }
        }

        if(!username.empty() && !password.empty()) {
            customers.push_back(newCustomer);    
        }
    }
    file.close();

    ifstream carFile("cars.txt");
    if(!carFile) {
        initializeCars();
        return;
    }
    cars.clear();
    while (getline(carFile, line)) {
        istringstream ss(line);
        string brand, model, priceStr, availabilityStr;
        
        getline(ss, brand, ',');
        getline(ss, model, ',');
        getline(ss, priceStr, ',');
        getline(ss, availabilityStr);
    
        brand.erase(0, brand.find_first_not_of(" "));
        brand.erase(brand.find_last_not_of(" ") + 1);
    
        model.erase(0, model.find_first_not_of(" "));
        model.erase(model.find_last_not_of(" ") + 1);
    
        double price = stod(priceStr);
        bool isAvailable = (availabilityStr == " 1");
    
        cars.push_back(Car(brand, model, price, isAvailable));
    }
    carFile.close();
}
};

#endif