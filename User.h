#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;
class User{
    
    public:
    User(string username, string password){
        this->username = username;
        this->password = password;
    }

    string getUsername()const{
        return username;
    }
    string getPassword()const{
        return password;
    }
    
    // void changePassword(const string& newPass){
    //     password = newPass;
    }
    private:
    string username;
    string password;

};

#endif