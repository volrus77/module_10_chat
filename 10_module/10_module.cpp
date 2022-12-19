// 10-chat_from_classes_usser_message.cpp : 
#include "Message.h"
#include "User.h"
#include <iostream>
#include <vector>

int User::static_number_ = 0;  // инициализируем статическое поле в классе User для создания userID
const int toALL = 1;  // когда надо отправить всем, пишем адрес назначения toALL
const int tModerator = 2;  // адрес модератора

//int enterInChat(std::vector<User>& v)
//{
//	std::string login;
//	std::string password;
//	std::cout << "Введите логин: ";
//	std::cin >> login;
//	std::cout << "Введите пароль: ";
//	std::cin >> password;
//
//	std::cout << "Login: " << login << "\tPassword: " << password << std::endl;
//	for (auto& user : v)
//	{
//		if (user.getLogin() == login && user.getPassword() == password)
//		{
//			user.setActivNow();
//			std::cout << "Здравствуйте " << user.getLogin() << ", Вы вошли в чат!" << std::endl;
//			return user.getID(); // возвращает ID пользователя, если вход успешен
//		}
//	}
//	return 0;  // возвращает 0, если вход неуспешен
//}

const User* enterInChat(std::vector<User*>& v)
{
	std::string login;
	std::string password;
	std::cout << "Введите логин: ";
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
			return user; // возвращает ID пользователя, если вход успешен
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

//const Message* createMsg(std::vector<User*>& vpU, const User* user)
//{
//
//	std::string text;
//	std::cout << "Введите сообщение: ";
//	std::cin >> text;
//	std::string login;
//	std::cout << "Введите логин получателя сообщения: ";
//	std::cin >> login;
//
//	return &Message(text, searchIDbyLogin(vpU, login), user->getID());
//}



int main()
{
	setlocale(LC_ALL, "");

	User all("loginall", "passwordall", "Nameall"); // Первым создаём пользователя all, его ID = 1
	//User* pAll= &all;
	User moderator("loginm", "passwordm", "Namem"); // Затем создаём модератора, его ID = 2
	//User* pModerator = &moderator;
	User user1("login1", "password1", "Name1");
	//User* pUser1 = &usser1;
	User user2("login2", "password2", "Name2");
	//User* pUser2 = &user2;
	User user3("login3", "password3", "Name3");
	//User* pUser3 = &user3;
	//std::vector<User> vUsers{all, moderator, user1, user2, user3 };
	std::vector<User*> vpUsers{ &all, &moderator, &user1, &user2, &user3 };

	Message msg1("Привет, не виделись сто лет.", user2.getID(), user1.getID());
	Message msg2("Хорошая погода!", user3.getID(), user2.getID());
	Message msg3("Как дела?", user1.getID(), user3.getID());
	Message msg4("Всем, всем, всем!!! Общий привет!!!", toALL, user2.getID());

	std::vector<Message*> vpMsg{ &msg1, &msg2, &msg3, &msg4 };

	bool work = true;
	while (work)
	{

		const User* entered = enterInChat(vpUsers);
		if (entered)
		{
			for (const auto& msg : vpMsg)
			{
				if (msg->getTo() == toALL)
				{
					std::cout << "Сообщение для всех: " << msg;
					/*int choice;
					std::cout << "Выберете: 1 - ответить, 2 - написать другому пользователю, 3 - выйти из чата.";
					std::cin >> choice;

					switch (choice)
						case 1:*/


				}
				if (msg->getTo() == entered->getID())
				{
					std::cout << "Сообщение от: " << searchUserByID(vpUsers, msg->getFrom())->getLogin()
						<< ": " << msg;
				}
			}
		}
		else
		{
			std::cout << "Ошибка при входе." << std::endl;

		}

	}


	return 0;
}


