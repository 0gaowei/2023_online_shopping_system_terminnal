#pragma once

#include "login.h"

class Register {
    public:
        Register(const string& nickname, const string& username, const string& password,
                 const string& phone, const string& birthday, const string& gender);
        
        // 注册成功欢迎
        void welcomeMenu();
        
        // 注册登记用户
        void registerUser();
    private:
        
        // 加载文件
        bool loadFile(const string& filename, const string& mode, std::fstream& file);
        
        //个人信息
        string username;
        string password;
        string nickname;
        string phone;
        string birthday;
        string gender;
};
