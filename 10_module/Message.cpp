#include "Message.h"

// �����������
Message::Message(const std::string& text, int to, int from)
	: text_(text), to_(to), from_(from)
{}

// ������������� ��������<<
std::ostream& operator<<(std::ostream& out, const Message* msg)
{
	out << msg->text_ << std::endl;
	return out;
}