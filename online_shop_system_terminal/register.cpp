#include <time.h>
#include "register.h"


Register::Register(const string& username, const string& password, const string& nickname,
                   const string& phone, const string& birthday, const string& gender)
                :   username(username), password(password), nickname(nickname),
                    phone(phone), birthday(birthday), gender(gender) {}

bool Register::loadFile(const string& filename, const string& mode, std::fstream& file) {
    // 打开文件，以追加模式写入
    file.open(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file:  " << filename << std::endl;
        return false;
    }
    return true;
}

void Register::registerUser() {

    // 将用户信息写入文件
    std::fstream file;
    if (loadFile("user.txt", "a", file)) {
        // TODO: 判断用户名是否重复
        file << username << " " << password << " " << nickname << " "
             << phone << " " << birthday << " " << gender << "\n";
        file.close();
        welcomeMenu();
    }
}

void Register::welcomeMenu() {
    std::cout << "\n============================\n";
    std::cout << "Registration successful! Welcome to join 0GW store!\n";
     std::cout << "Return to homepage......\n";
    std::cout << "============================\n";
}
