# Sockets

This exercise utilizes sockets to send an encoded message between child processes.

Encoder acts as a server that receives messages from each child process, to be passed along to another child process. A single encoded signal is produced from all of the message values and child process using Walsh code. After all messages have been received and the signal is created, Encoder sends the signal back to each of the child processes, with the corresponding child process number needed to decode the message.

Sender reads an input file containing the message to be sent, and the child process the message should be sent to. As each line is read, the parent process forks a child process that then creates a socket to communicate with Encoder, and then writes the message to the Encoder's socket. The child process then waits for a response from Encoder, which will send the signal and key back to the child. Once the child process receives the encoded message, it will decode it based on the key.

Directions:
1. Run `make` in the `src/` directory to compile sender.cpp and encoder.cpp and any dependencies
2. Open new terminal session and navigate to the `src/` directory
3. Execute `./encode 5000`, with port number specified as 5000. This can be changed to any free port.
4. Switch to the other terminal session and execute `./send $(hostname) 5000 < input.txt`, with port number the same as the one specified when running `encode`.
