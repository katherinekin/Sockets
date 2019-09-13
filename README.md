# Sockets

This exercise looks

Sender.cpp
For each line read, forks a child process
Each child creates a socket to connect to the server
First set the port number and socket file descripter

Encoder.cpp
Encoder acts as the server
Creates a socket to receive messages from sender
store the child socket fd in the container client_socket
store the destination in the container dest_order
As each message is received from sender, encodes the messages was a key based on the child number using walsh code
After all messages are received, sends the messages to intended child based on file descriptor

Once sender receives the encoded message, it will decode it based on which child sent the message

Directions:
1. Run `make` in the `src/` directory to compile sender.cpp and encoder.cpp and any dependencies
2. Open new terminal session and navigate to the `src/` directory
3. Execute `./encode 5000`, with port number specified as 5000. This can be changed to any free port.
4. Switch to the other terminal session and execute `./send $(hostname) 5000 < input.txt`, with port number the same as the one specified when running `encode`.
