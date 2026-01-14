# Messaging System
This was inspired by a problem I was given during a graduate software interview. A system accepts messages every second, which needs to be processed at a certain timestamp.

I used two threads, one being a read thread which accepts messages once per second, the other being a processing thread, which processes the messages when they need to be processed.

# How to Run
```
git clone https://github.com/hrrydev/messaging-system
cd messaging-system
mkdir build
cd build
cmake ..
make && ./system
```
