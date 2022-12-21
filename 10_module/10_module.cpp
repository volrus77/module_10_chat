// 10-chat_from_classes_usser_message.cpp : 
#include "Message.h"
#include "User.h"
#include <iostream>
#include <vector>
#include <limits>

int User::static_number_ = 0;  // инициализируем статическое поле в классе User для создания userID
const int toALL = 1;  // когда надо отправить всем, пишем адрес назначения toALL
const int tModerator = 2;  // адрес модератора


bool registration(std::vector<User*>& v)
{
	std::string login;
	std::string password;
	std::cout << "Для регистрации введите логин: ";
	std::cin >> login;
	std::cout << "Введите пароль: ";
	std::cin >> password;
	std::cout << "Введите имя: ";
	std::string name;
	std::cin >> name;

	User* us = new User(login, password, name);
	v.push_back(us);
	std::cout << login << " Вы зарегистрированы." << std::endl;
	return true;
}

 User* enterInChat(std::vector<User*>& v)
{
	std::string login;
	std::string password;
	std::cout << "Для входа введите логин: ";
	std::cin >> login;
	std::cout << "Введите пароль: ";
	std::cin >> password;

	std::cout << "Login: " << login << "\tPassword: " << password << std::endl;
	for (auto& user : v)
	{
		if (user->getLogin() == login && user->getPassword() == password)
		{
			user->setActivNow();
			std::cout << "Здравствуйте " << user->getLogin() << ", Вы вошли в чат!" << std::endl;
			return user; // возвращает указатель на пользователя, если вход успешен
		}
	}
	return nullptr;  // возвращает 0, если вход неуспешен
}

const User* searchUserByID(std::vector<User*>& vpU, int id)
{
	for (const auto pUser : vpU)
	{
		if (pUser->getID() == id)
			return pUser;
	}
	return nullptr;
}

int searchIDbyLogin(std::vector<User*>& vpU, const std::string& login)
{
	for (const auto& pUser : vpU)
	{
		if (pUser->getLogin() == login)
			return pUser->getID();
	}
	return 0;
}

void writeMessage(std::vector<User*>& vpU, std::vector<Message*>& vpMs, int id_from)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Введите логин получателя сообщения: ";
	std::string login;
	std::cin >> login;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Введите сообщение: ";
	std::string text;
	std::getline(std::cin, text);
	
	Message* ms =  new Message(text, searchIDbyLogin(vpU, login), id_from );
	vpMs.push_back(ms);
}

void writeMessage(std::vector<User*>& vpU, std::vector<Message*>& vpMs, int id_to, int id_from)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Введите сообщение: ";
	std::string text;
	std::getline(std::cin, text);

	Message* ms =  new Message(text, id_to, id_from);
	vpMs.push_back(ms);
}


int main()
{
	setlocale(LC_ALL, "");

	User all("loginall", "passwordall", "Nameall"); // Первым создаём пользователя all, его ID = 1
	User moderator("loginm", "passwordm", "Namem"); // Затем создаём модератора, его ID = 2
	//User user1("login1", "password1", "Name1");
	//User user2("login2", "password2", "Name2");
	//User user3("login3", "password3", "Name3");

	std::vector<User*> vpUsers{ &all, &moderator };

	registration(vpUsers);
	registration(vpUsers);

	//Message msg1("Привет, не виделись сто лет.", user2.getID(), user1.getID());
	//Message msg2("Хорошая погода!", user3.getID(), user2.getID());
	//Message msg3("How are you?", user1.getID(), user3.getID());
	//Message msg4("Всем, всем, всем!!! Общий привет!!!", toALL, user2.getID());

	//std::vector<Message*> vpMsg{ &msg1, &msg2, &msg3, &msg4 };
	std::vector<Message*> vpMsg{ };

	bool work = true;
	while (work)
	{

		User* entered = enterInChat(vpUsers);
		if (entered)
		{
			bool processed = false;
			for (const auto& msg : vpMsg)
			{
				int it_to = msg->getTo();
				if (it_to == entered->getID() || it_to == toALL)
				{
					std::cout << "Сообщение от: " << searchUserByID(vpUsers, msg->getFrom())->getLogin()
						<< ": " << msg;
					int choice;
					std::cout << "Выберете: 1 - ответить, 2 - написать другому пользователю, 3 - выйти из чата."
						<< "4 - выйти из программы.";
					std::cin >> choice;

					if (choice == 1)
					{
						writeMessage(vpUsers, vpMsg, msg->getFrom(), entered->getID());
						entered->setDeactivNow();
						std::cout << entered->getLogin() << ", вы вышли из чата!!!" << std::endl;
						processed = true;
						break;
					}
					if (choice == 2)
					{
						writeMessage(vpUsers, vpMsg, entered->getID());
						entered->setDeactivNow();
						std::cout << entered->getLogin() << ", вы вышли из чата!!!" << std::endl;
						processed = true;
						break;
					}
					if (choice == 3)
					{
						entered->setDeactivNow();
						std::cout << entered->getLogin() << ", вы вышли из чата!!!" << std::endl;
						processed = true;
						break;
					}
					if (choice == 4)
					{
						entered->setDeactivNow();
						processed = true;
						work = false;
						break;
					}
				}
			}
			if (!processed)
			{
				std::cout << "Для вас сегодня нет сообщений." << std::endl;
				writeMessage(vpUsers, vpMsg, entered->getID());
				std::cout << entered->getLogin() << ", вы вышли из чата!!!" << std::endl;
			}
		}
		else
		{
			std::cout << "Ошибка при входе." << std::endl;

		}

	}

	std::cout << "Выход из программы.";
	return 0;
}


