#include "guest.h"
#include "login.h"
#include "register.h"

int main() {
	int choice = - 1;

	do {
		std::cout << "\n****Welcome to 0GW online shopping system!****" << std::endl;
		std::cout << "╔═══════════════════════════╗" << std::endl;
		std::cout << "║ 1. Admin login            ║" << std::endl;
		std::cout << "║ 2. User login             ║" << std::endl;
		std::cout << "║ 3. User registration      ║" << std::endl;
		std::cout << "║ 4. Visitor browsing       ║" << std::endl;
		std::cout << "║ 0. Exit the system        ║" << std::endl;
		std::cout << "╚═══════════════════════════╝" << std::endl;

		std::cout << "\nPlease enter your choice: ";
		std::cin >> choice;
		Guest guest;
		
		if (choice == 1) {
			std::cout << "\n==============================\n";
			std::cout << "Admin logining\n";
			std::cout << "==============================\n";
			string username, password;
			std::cout << "\nPlease enter the admin username: ";
			std::cin >> username;
			std::cout << "\nPlease enter admin password: ";
        	std::cin >> password;

			// 尝试登录，以管理员身份
			const string userType = "admin";
			Login logining(userType, username, password);
			logining.tryLogin("admin");
		} else if (choice == 2) {
			std::cout << "============================\n";
			std::cout << "User logining\n";
			std::cout << "============================\n";
			string username, password;
			std::cout << "\nPlease enter the user name: ";
			std::cin >> username;
			std::cout << "\nPlease enter user password: ";
			std::cin >> password;

			// 尝试登录，以顾客身份
			const string userType = "user";
			Login logining(userType, username, password);
			logining.tryLogin("user");
		} else if (choice == 3)	{
			std::cout << "\n============================\n";
			std::cout << "Welcome to register 0GW's store! \n";
			std::cout << "============================\n";
			
			// 尝试注册
			string nickname, username, password, phone, birthday, gender;
			// std::string captcha; // 验证码
			
			/*// 生成验证码
			srand(static_cast<unsigned>(time(0)));
			int generatedCaptcha = rand() % 10000;
			std::cout << "验证码：" << generatedCaptcha << "\n请输入验证码：";
			std::cin >> captcha;
			*/
			// 收集新用户信息
			std::cout << "Please enter a nickname:";
			std::cin >> nickname;
			std::cout << "Please enter username:";
			std::cin >> username;
			std::cout << "Please enter password:";
			std::cin >> password;
			std::cout << "Please enter your mobile phone number:";
			std::cin >> phone;
			std::cout << "Please enter birthday:";
			std::cin >> birthday;
			std::cout << "Please enter gender:";
			std::cin >> gender;

			
			Register registering(username, password, nickname, phone, birthday, gender);
			// 登记新用户信息
			registering.registerUser();
			

		} else if (choice == 4)	{
			std::cout << "============================\n";
			std::cout << "    Visitor browsing\n";
			guest.browse();
			std::cout << "============================\n";
		} else if (choice == 0) {
			std::cout << "Exiting......\n";
			break;
		} else {
			std::cout << "Invalid selection, please re-enter\n";
		}//if

	} while (choice != 0);

	return 0;
}//main
