# HTTP Server in C++ - A Beginner's Guide

## 📚 Table of Contents
- [What is Socket Programming?](#what-is-socket-programming)
- [Project Overview](#project-overview)
- [How Internet Communication Works](#how-internet-communication-works)
- [Project Structure](#project-structure)
- [Understanding the Code](#understanding-the-code)
- [Key Concepts Explained](#key-concepts-explained)
- [How to Build and Run](#how-to-build-and-run)
- [Next Steps](#next-steps)

---

## 🌐 What is Socket Programming?

Imagine you want to make a phone call to your friend:
1. You **dial** their number (create a connection)
2. They **answer** (accept the connection)
3. You both **talk** (send and receive data)
4. You **hang up** (close the connection)

**Socket programming is exactly the same, but for computers!** A socket is like a phone that allows two computers to talk to each other over the internet.

### Real-World Example
When you visit `www.google.com`:
- Your browser (client) creates a socket
- Google's server has a socket listening for connections
- They connect and exchange data (your search request and results)
- The connectionexi closes when done

---

## 🎯 Project Overview

This project is building an **HTTP Server** in C++ from scratch. An HTTP server is a program that:
- Waits for clients (like web browsers) to connect
- Receives requests (like "give me the homepage")
- Sends back responses (like HTML, images, or data)

Think of it like a waiter at a restaurant:
- **Listening**: Waiting for customers to arrive
- **Accepting**: Seating customers at tables
- **Serving**: Taking orders and bringing food
- **Closing**: Clearing tables when customers leave

---

## 🔌 How Internet Communication Works

### The OSI Model (Simplified)

Think of sending a letter through the postal service:

1. **Application Layer** (HTTP, FTP, SMTP)
   - You write the letter content
   - Like: "GET /index.html" in HTTP

2. **Transport Layer** (TCP, UDP)
   - You put it in an envelope with addresses
   - TCP ensures reliable delivery (like registered mail)
   - UDP is faster but doesn't guarantee delivery (like regular mail)

3. **Internet Layer** (IP)
   - The postal service routes it through cities
   - IP addresses are like street addresses

4. **Physical Layer** (Cables, WiFi)
   - The actual trucks and planes carrying mail
   - The physical wires and radio waves

### IP Addresses and Ports

- **IP Address**: Like a building's street address (e.g., 192.168.1.1)
- **Port**: Like an apartment number in that building (e.g., 80 for HTTP, 443 for HTTPS)

Example: `192.168.1.1:8080` means "building at 192.168.1.1, apartment 8080"

---

## 📁 Project Structure

```
http-server/
├── Networking/
│   ├── SimpleSocket.hpp       # Socket class header (interface)
│   └── SimpleSocket.cpp       # Socket class implementation
├── berner.hpp                 # Main server header
├── berner.cpp                 # Main server implementation
└── README.md                  # This file
```

---

## 🧩 Understanding the Code

### 1. SimpleSocket Class (`Networking/SimpleSocket.hpp`)

This is the foundation - it creates and manages a socket (the communication endpoint).

#### Key Components:

```cpp
class SimpleSocket {
    private:
        struct sockaddr_in address;  // Socket address (IP + Port)
        int sock;                    // Socket file descriptor (ID)
        int connection;              // Connection status
```

**What's happening?**

- `sockaddr_in address`: A structure that holds:
  - **IP address**: Where to send/receive data
  - **Port number**: Which application to communicate with
  - **Address family**: IPv4 or IPv6

- `int sock`: A number (file descriptor) that identifies your socket
  - In Unix/Linux, everything is a file - even network connections!
  - This number is like a handle to access your socket

- `int connection`: Status of the connection (success or failure)

#### Constructor Parameters:

```cpp
SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
```

Let's break down each parameter:

1. **`domain`** (Address Family):
   - `AF_INET`: Use IPv4 addresses (like 192.168.1.1)
   - `AF_INET6`: Use IPv6 addresses (like 2001:0db8::1)
   - Think of it as choosing between a local phone number or international

2. **`service`** (Socket Type):
   - `SOCK_STREAM`: TCP - reliable, ordered delivery (like registered mail)
   - `SOCK_DGRAM`: UDP - fast but unreliable (like postcards)
   - For HTTP, we use TCP because we need reliable data transfer

3. **`protocol`**:
   - Usually `0` (let the system choose based on service)
   - Can specify specific protocols like `IPPROTO_TCP`

4. **`port`**:
   - Port number (0-65535)
   - Well-known ports: 80 (HTTP), 443 (HTTPS), 22 (SSH)
   - Ports 0-1023 require admin privileges

5. **`interface`**:
   - Which network interface to bind to
   - `INADDR_ANY`: Accept connections from any network interface
   - Specific IP: Only accept connections on that interface

#### Virtual Method:

```cpp
virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
```

This is a **pure virtual function** (abstract method):
- The `= 0` means subclasses **must** implement this
- Different for servers (bind/listen/accept) vs clients (connect)
- Allows us to create different socket types from the same base class

### 2. SimpleSocket Implementation (`Networking/SimpleSocket.cpp`)

```cpp
HDE::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface) {
    address.sin_family = domain;              // Set IPv4 or IPv6
    address.sin_port = htons(port);           // Set port (converted to network byte order)
    address.sin_addr.s_addr = htonl(interface); // Set IP address
    sock = socket(domain, service, protocol); // Create the socket
    connection = connect_to_network();        // Connect/bind the socket
}
```

**What's `htons()` and `htonl()`?**

Different computers store numbers differently:
- **Little Endian**: Number 1234 stored as [34, 12]
- **Big Endian**: Number 1234 stored as [12, 34]

Networks always use **Big Endian** (network byte order):
- `htons()`: **H**ost **to** **N**etwork **S**hort (converts port numbers)
- `htonl()`: **H**ost **to** **N**etwork **L**ong (converts IP addresses)

This ensures computers with different architectures can communicate!

### 3. Namespace Organization

```cpp
namespace HDE {
    // All classes here
}
```

Namespaces prevent naming conflicts:
- Like having two people named "John" - you'd use last names to distinguish
- `HDE::SimpleSocket` vs `AnotherLibrary::SimpleSocket`

---

## 🔑 Key Concepts Explained

### 1. The Socket Lifecycle (Server Side)

```
1. socket()    → Create a socket (get a phone)
2. bind()      → Bind to an address (get a phone number)
3. listen()    → Listen for connections (answer incoming calls)
4. accept()    → Accept a connection (pick up the phone)
5. send/recv() → Exchange data (talk)
6. close()     → Close connection (hang up)
```

### 2. The Socket Lifecycle (Client Side)

```
1. socket()    → Create a socket (get a phone)
2. connect()   → Connect to server (dial a number)
3. send/recv() → Exchange data (talk)
4. close()     → Close connection (hang up)
```

### 3. TCP vs UDP

| Feature | TCP (SOCK_STREAM) | UDP (SOCK_DGRAM) |
|---------|-------------------|------------------|
| **Reliability** | Guaranteed delivery | No guarantee |
| **Order** | Packets arrive in order | May arrive out of order |
| **Speed** | Slower (overhead) | Faster |
| **Connection** | Connection-oriented | Connectionless |
| **Use Case** | Web, Email, File Transfer | Gaming, Video Streaming, DNS |

**Analogy:**
- **TCP**: Like a phone call - connection established, guaranteed delivery
- **UDP**: Like sending postcards - fire and forget, may get lost

### 4. Blocking vs Non-Blocking

- **Blocking**: Function waits until data arrives (like waiting for mail)
- **Non-blocking**: Function returns immediately even if no data (peek at mailbox)

### 5. File Descriptors

In Unix/Linux, everything is a file:
- Regular files
- Directories
- Sockets
- Pipes
- Devices

A file descriptor is just a number that identifies which "file" you're working with.

---

## 🛠️ How to Build and Run

### Prerequisites

- C++ compiler (g++ or clang++)
- Linux/Unix environment (uses POSIX sockets)
- Basic terminal knowledge

### Compilation

```bash
# Compile the socket library
g++ -c Networking/SimpleSocket.cpp -o SimpleSocket.o

# Compile main program (when complete)
g++ -c berner.cpp -o berner.o

# Link everything
g++ SimpleSocket.o berner.o -o http-server

# Run the server
./http-server
```

### Testing

Once the server is running:

```bash
# In another terminal, test with curl
curl http://localhost:8080

# Or open in a web browser
# Navigate to: http://localhost:8080
```

---

## 🚀 Next Steps

To complete this HTTP server, you'll need to:

1. **Create Server Socket Subclass**
   - Implement `connect_to_network()` to use `bind()`, `listen()`, `accept()`
   - Create a `ListeningSocket` or `ServerSocket` class

2. **Handle HTTP Requests**
   - Parse incoming HTTP requests (GET, POST, etc.)
   - Extract URL, headers, and body

3. **Generate HTTP Responses**
   - Create proper HTTP response format
   - Set status codes (200 OK, 404 Not Found, etc.)
   - Add headers (Content-Type, Content-Length)

4. **Serve Static Files**
   - Read HTML, CSS, JS, images from disk
   - Send them to clients

5. **Handle Multiple Connections**
   - Use threads or async I/O
   - Prevent one slow client from blocking others

6. **Error Handling**
   - Handle network errors gracefully
   - Validate input
   - Log errors

### Learning Resources

- **Beej's Guide to Network Programming**: Comprehensive socket programming guide
- **RFC 2616**: HTTP/1.1 specification
- **"Unix Network Programming" by W. Richard Stevens**: The bible of network programming

---

## 📝 Common Socket Functions Reference

| Function | Purpose | Example |
|----------|---------|---------|
| `socket()` | Create a socket | `socket(AF_INET, SOCK_STREAM, 0)` |
| `bind()` | Bind socket to address | `bind(sock, &addr, sizeof(addr))` |
| `listen()` | Listen for connections | `listen(sock, BACKLOG)` |
| `accept()` | Accept a connection | `accept(sock, NULL, NULL)` |
| `connect()` | Connect to server | `connect(sock, &addr, sizeof(addr))` |
| `send()` | Send data | `send(sock, data, len, 0)` |
| `recv()` | Receive data | `recv(sock, buffer, size, 0)` |
| `close()` | Close socket | `close(sock)` |

---

## 🐛 Current Issues to Fix

The code has a few syntax errors that need correction:

1. **SimpleSocket.hpp (Line 15)**: Missing comma
   ```cpp
   // Current:
   SimpleSocket(int domain,int service int protocol,...
   
   // Should be:
   SimpleSocket(int domain, int service, int protocol,...
   ```

2. **SimpleSocket.cpp (Line 8)**: Incorrect function call
   ```cpp
   // Current:
   connection = connect_to_network();
   
   // Should be:
   connection = connect_to_network(sock, address);
   ```

---

## 📖 Glossary

- **Socket**: Endpoint for network communication
- **TCP**: Transmission Control Protocol (reliable)
- **UDP**: User Datagram Protocol (fast, unreliable)
- **IP**: Internet Protocol (addressing)
- **Port**: Application identifier on a host
- **Bind**: Associate socket with address
- **Listen**: Wait for incoming connections
- **Accept**: Accept incoming connection
- **HTTP**: HyperText Transfer Protocol (web communication)
- **File Descriptor**: Integer identifier for open file/socket
- **Byte Order**: How multi-byte numbers are stored (endianness)

---

## 🤝 Contributing

This is a learning project! Feel free to:
- Fix bugs
- Add features
- Improve documentation
- Share your understanding

---

## 📄 License

[Add your license here]

---

**Happy Coding! 🚀**

*Remember: Every expert was once a beginner. Take your time understanding each concept!*
