// 10-chat_from_classes_usser_message.cpp :
#include "Message.h"
#include "User.h"
#include <iostream>
#include <vector>
#include <limits>

int User::static_number_ = 0;  // инициализируем статическое поле в классе User для создания userID
const int toALL = 1;  // когда надо отправить всем, пишем адрес назначения toALL
const int tModerator = 2;  // адрес модератора

// функция регистрации пользователя, пользователь сохраняется в векторе
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

// функция входа в чат
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

const std::string& searchLoginByID(std::vector<User*>& vpU, int id)
{
	for (const auto pUser : vpU)
	{
		if (pUser->getID() == id)
			return pUser->getLogin();
	}
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

// пишем сообщение, логин получателя запрашиваем с клавиатуры
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
	
	Message* ms =  new Message(text, searchIDbyLogin(vpU, login), id_from ); // использую new без delete
	vpMs.push_back(ms);
}

// пишем сообщение как ответ, т. е. когда известен получатель
void writeMessage(std::vector<User*>& vpU, std::vector<Message*>& vpMs, int id_to, int id_from)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Введите сообщение: ";
	std::string text;
	std::getline(std::cin, text);

	Message* ms =  new Message(text, id_to, id_from);  // использую new без delete
	vpMs.push_back(ms);
}


int main()
{
	setlocale(LC_ALL, "");

	User all("loginall", "passwordall", "Nameall"); // Первым создаём пользователя all, его ID = 1
	User moderator("loginm", "passwordm", "Namem"); // Затем создаём модератора, его ID = 2

	std::vector<User*> vpUsers{ &all, &moderator };   // создаём вектор для пользователей

	registration(vpUsers);  // регистрируем двух плользователей
	registration(vpUsers);

	std::vector<Message*> vpMsg{ };  // создаём вектор для сообщений

	bool work = true;
	while (work)   //  основной цикл чата
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
					std::cout << "Сообщение от: " << searchLoginByID(vpUsers, msg->getFrom())
						<< ": " << msg;
					int choice;
					std::cout << "Выберете: 1 - ответить, 2 - написать другому пользователю, 3 - выйти из чата, "
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


