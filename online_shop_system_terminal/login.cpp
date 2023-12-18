#include "login.h"
#include <sstream>

Login::Login(const string& userType, string& username, string& password)
            : userType(userType), username(username), password(password) {}

// 检查是否合法用户
string Login::isLegitimateUser() {
    string line;
    std::ifstream userFile;
    string storedUsername, storedPassword;
    if (userType == "admin") {
    // 管理员登录,读取管理员数据库，判断是否为管理员
        int cnt = 2;
        do {
            userFile.open(userType + ".txt", std::ios::in);
            while (std::getline(userFile, line)) {
                std::stringstream ss(line);
                ss >> storedUsername >> storedPassword >> nickname;
                if (storedUsername == username && storedPassword == password && storedUsername != "FAIL") {
                    userFile.close();
                    return username; // 管理员验证成功
                }
            }
            std::cout << "\nWrong password, please re-enter the password (you only have " << cnt-- << " chances left): ";
            userFile.close();
            std::cin >> password;
        } while (cnt > 0);
        userFile.close();
        return "FAIL"; // 管理员验证失败

    } else if (userType == "user") {
    // 用户登录，读取用户数据库，判断是否为已注册的用户
        int cnt = 2;
        do {
            userFile.open(userType + ".txt", std::ios::in);
            while (std::getline(userFile, line)) {
                std::stringstream ss(line);
                ss >> storedUsername >> storedPassword >> nickname >> phone >> birthday >> gender;
                if (storedUsername == username && storedPassword == password && storedUsername != "FAIL") {
                    userFile.close();
                    return username; // 用户验证成功
                }
            }
            std::cout << "\nWrong password, please re-enter the password (you have " << cnt-- << " opportunities): ";
            userFile.close();
            std::cin >> password;
        } while (cnt > 0);
        userFile.close();
        return "FAIL"; // 用户验证失败

    // 无法读取数据库
    } else {
        std::cerr << "Failed to open the user file!\n";
        return "FAIL";
    }//if

    return "FAIL"; // 验证失败
}//isLegitimateUser

void Login::tryLogin(const string& userType) {
    // 管理员登录，invoke isLeg... judgment function
    if (userType == "admin") {
        if (isLegitimateUser() != "FAIL") {
            Admin admin(nickname, username); // create an admin object
            admin.welcomeMenu();
        } else {
            std::cout << "\nFailed to log in. Returning to the home page...\n";
        }

    // 用户登录，invoke isLeg... judgment function
    } else {
        if (isLegitimateUser() != "FAIL") {
            User user(username, password, "", "", "", "");    //create a user object
            user.welcomeMenu();
        } else {
            std::cout << "\nFailed to log in. Returning to the home page...\n";
        }
    }
}
