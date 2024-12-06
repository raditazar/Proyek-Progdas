#include <iostream>
#include "Rental.h"
using namespace std;
int main() {
    Rental rental;

    while (true) {
        cout << "\n----- Car Rental System -----\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Login as admin\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        

        switch (choice) {
            case 1:
                rental.signUp();
                break;
            case 2: {
                Customer* customer = rental.login();
                if (customer) {
                    rental.displayMenu();
                }
                break;
            }
            case 3:{
                Admin* admin = rental.adminLogin();
                if (admin) {
                    rental.adminMenu();
                }
                break;
            }
            case 4:
                cout << "Thank you for using Car Rental System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}