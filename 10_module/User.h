#pragma once
#include <string>
class User
{
public:
	// конструктор и деструктор
	User(const std::string&, const std::string&, const std::string&);
	virtual ~User() = default;

	// геттеры
	const std::string& getLogin() const { return login_; }
	const std::string& getPassword() const { return password_; }
	const std::string& getName() const { return name_; }
	bool isActivNow() { return isActivNow_; }
	const int getID() const { return userID_; }

	// сеттеры
	void setActivNow() { isActivNow_ = true; }
	void setDeactivNow() { isActivNow_ = false; }

private:
	std::string login_;
	std::string password_;
	std::string name_;
	bool isActivNow_{ false };
	static int static_number_;
	int userID_;
};

