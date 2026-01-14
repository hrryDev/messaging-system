# Messaging System
This was inspired by a problem I was given during a graduate software interview. A system accepts messages every second, which needs to be processed at a certain timestamp.

The system uses two thread-types, one being the reader, and the other being the processor. A single read thread is responsible for accepting messages and placing them into a priority queue, with the message timestamp as the priority attribute. This ensures the message with the earliest timestamp is at the front of the queue.

There can be many processing threads, which constantly check if the message in the front of the queue needs to be processed right now. If the message needs to be processed, it will be removed from the queue and processed for 1 second, simulating complex processing logic.

# How to Run
```
git clone https://github.com/hrrydev/messaging-system
cd messaging-system
mkdir build
cd build
cmake ..
make && ./system
```
