#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
class Admin: public User{
    public: 
        Admin(string username, string password, bool isAdmin = false)
            :User(username, password), isAdmin(isAdmin){}

        bool getAdminStatus()const{
            return isAdmin;
        }

    
        

    private:
        bool isAdmin;

};
#endif