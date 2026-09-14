run : build
	./server
    
build:
	g++ Networking/BindingSocket.cpp Networking/ListeningSocket.cpp Networking/ConnectingSocket.cpp Networking/SimpleSocket.cpp berner.cpp -o server