#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include "admin.h"
#include "usr.h"

class Login {
    public:
        Login(const string& userType, string& username, string& password);
        // 尝试登录
        void tryLogin(const string& userType);

    private:
        const string userType;
        string name, username, password, nickname, phone, birthday, gender;
        // 判断是否合法用户
        string isLegitimateUser();
};
