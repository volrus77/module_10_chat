#pragma once
#include <string>
#include <iostream>

class Message
{
public:
	//  ����������� � ����������
	Message(const std::string& text, int to, int from);

	virtual ~Message() = default;


	// ��������
	const std::string& getText() const { return text_; }
	int getTo() { return to_; }
	int getFrom() { return from_; }

	// ������������� ��������<<
	friend std::ostream& operator<<(std::ostream& out, const Message* msg);

private:
	std::string text_;  // text of message
	int to_{ 0 };  // UserID_to
	int from_{ 0 };  // UserID_from
};


