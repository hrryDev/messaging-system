#ifndef PROCESS
#define PROCESS

#include "message.h"
#include "MessageCompare.h"

#include <thread>
#include <queue>
#include <vector>

class Process {
	public:
		/**
		 * Starts the message processing system.
		 *
		 * @param num_processing_threads How many threads to spawn for processing the messages.
		 */
		Process(int num_processing_threads);
		~Process();
	private:
		int count;
		std::mutex queue_access;
		std::priority_queue<Message, std::vector<Message>, MessageCompare> message_queue;

		std::thread receive_thread;
		std::vector<std::thread> processing_threads;

		/**
		 * Custom comparison function for the priority queue.
		 *
		 * @param a The first message to compare.
		 * @param b The second message to compare
		 * @return Whether the timestamp of the first message is earlier than the second message.
		 */
		bool Compare(Message a, Message b);

		/**
		 * Message reading thread.
		 *
		 * Waits for a message to come through from read(), then adds it to the message_queue with the priority being the earliest timestamp.
		 */
		void read_thread();


		/**
		 * Read a message.
		 *
		 * Simulates receiving a message by creating a message with a random timestamp.
		 *
		 * @return Returns the message.
		 */
		Message read();

		/**
		 * Processing thread.
		 *
		 * Waits for the message_queue to be available, then checks if the highest priority message needs to be processed.
		 *
		 * If it does, it pops the message off the queue, and processes it with process_message().
		 */
		void processing_thread();

		
		/**
		 * Process a given message.
		 *
		 * Simulates processing a message by printing it to the
		 * console and waiting 1 second.
		 *
		 * @param msg Message to be processed.
		 */
		void process_message(Message msg);
};

#endif // !PROCESS
