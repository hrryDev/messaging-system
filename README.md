# Messaging System
This was inspired by a problem I was given during a graduate software interview. A system accepts messages every second, which needs to be processed at a certain timestamp.

I used two threads, one being a read thread which accepts messages once per second, the other being a processing thread, which processes the messages when the need to be processed.
