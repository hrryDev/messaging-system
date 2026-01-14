#ifndef MESSAGE
#define MESSAGE

#include <chrono>
#include <string>

class Message {
	public:
		int id;
		std::chrono::system_clock::time_point timestamp;
		std::string body;
};

#endif // !MESSAGE
