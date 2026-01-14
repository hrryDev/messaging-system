#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib>
#include <semaphore>

std::binary_semaphore queue_access{1};

class Message {
	public:
		std::chrono::system_clock::time_point timestamp;
		std::string body;
};

bool Compare(Message a, Message b) {
	return a.timestamp > b.timestamp;
}

std::priority_queue<Message, std::vector<Message>, decltype(&Compare)> message_queue(Compare);

Message read() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Message msg;
	int delay = rand() % 101;
	msg.timestamp = std::chrono::system_clock::now() + std::chrono::seconds(delay);
	msg.body = "test message";

	return msg;
}

void receive_message() {
	std::cout << "[read_thread]: created!" << std::endl;

	while (true) {
		Message msg = read();
		std::cout << std::chrono::system_clock::now() << " [read_thread]: message received! " << msg.timestamp << std::endl;
		queue_access.acquire();
		message_queue.push(msg);
		queue_access.release();
	}
}

int process_message() {
	std::cout << "[processing_thread]: created!" << std::endl;
	
	while (true) {
		queue_access.acquire();
		if (!message_queue.empty()) {
			Message msg = message_queue.top();
			if (std::chrono::system_clock::now() > msg.timestamp) {
				std::cout << std::chrono::system_clock::now() << " [processing_thread]: message processed = " << msg.timestamp << " " << msg.body << std::endl;
				message_queue.pop();
			}
		}
		queue_access.release();
	}

	return 0;
}

int main() {
	srand(time(0));

	std::thread read_thread(receive_message);
	std::thread processing_thread(process_message);
	
	read_thread.detach();
	processing_thread.detach();
	
	while (true) {}

	return 0;
}
