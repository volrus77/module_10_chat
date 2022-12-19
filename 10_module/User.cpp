#include "User.h"

// конструктор
User::User(const std::string& login, const std::string& password, const std::string& name)
	: login_(login), password_(password), name_(name)
{
	++User::static_number_;
	userID_ = User::static_number_;
}


