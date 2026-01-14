#include "process.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

Process::Process(int num_processing_threads) {
	srand(time(0));

	Process::count = 0;

	std::thread receive_thread(&Process::read_thread, this);
	std::vector<std::thread>processing_threads(num_processing_threads);
	for (auto &t : processing_threads) t = std::thread(&Process::processing_thread, this);

	receive_thread.detach();
	for (auto &t : processing_threads)
		t.detach();
}

Process::~Process() {
	if (receive_thread.joinable())
		receive_thread.join();
	
	for (auto &t : processing_threads)
		if (t.joinable())
			t.join();
}

void Process::read_thread() {
	while (true) {
		Message msg = read();
		std::cout << std::chrono::system_clock::now() << " [read_thread]: message received! " << msg.id << " " << msg.timestamp << std::endl;
		queue_access.lock();
		Process::message_queue.push(msg);
		queue_access.unlock();
	}
}

Message Process::read() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	Message msg;
	int delay = rand() % 101;
	msg.timestamp = std::chrono::system_clock::now() + std::chrono::seconds(delay);
	msg.id = count;
	++count;
	msg.body = "test message";

	return msg;
}

void Process::process_message(Message msg) {
	std::cout << std::chrono::system_clock::now() << " [processing_thread]: message processed = " << msg.id << " " << msg.timestamp << " " << msg.body << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Process::processing_thread() {
	bool process = false;
	Message msg;

	while (true) {
		process = false;
		queue_access.lock();
		if (!message_queue.empty()) {
			msg = message_queue.top();
			if (std::chrono::system_clock::now() > msg.timestamp) {
				process = true;
				message_queue.pop();
			}
		}
		queue_access.unlock();

		if (process) process_message(msg);
	}
}
