#pragma once

#include <string>
using std::string;

class Admin {
public:
    Admin(const string& nickname, const string& username);
    void welcomeMenu();
    bool addGood(string id, string name, double price,
                    string info, int total);
    bool deleteGood(string id);
    bool modifyGood(string id);
    // TODO: 添加商品（ID，名称，单价，描述，库存），删除商品，修改商品信息
private:
    string nickname;
    string username;
    string password;
};
