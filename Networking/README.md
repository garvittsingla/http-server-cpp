# Socket Programming Documentation

## Table of Contents
1. [What is Socket Programming?](#what-is-socket-programming)
2. [Basic Concepts](#basic-concepts)
3. [Your Code Explained](#your-code-explained)
4. [Function and Parameter Details](#function-and-parameter-details)
5. [How It All Works Together](#how-it-all-works-together)

---

## What is Socket Programming?

**Socket programming** is a way for programs to communicate over a network (like the internet) or even on the same computer. Think of a socket as a "phone line" that allows two programs to talk to each other.

### Real-World Analogy
- **Socket** = A telephone
- **IP Address** = A phone number
- **Port** = An extension number
- **Connection** = An active phone call

When you visit a website, your browser uses sockets to "call" the web server and request web pages.

---

## Basic Concepts

### 1. What is a Socket?
A **socket** is an endpoint for sending or receiving data across a network. It's created by combining:
- An **IP address** (identifies the computer)
- A **port number** (identifies the specific application/service on that computer)

### 2. Types of Sockets
- **Stream Sockets (TCP)**: Reliable, ordered, like a phone call - guaranteed delivery
- **Datagram Sockets (UDP)**: Fast but unreliable, like sending postcards - might get lost

### 3. Client vs Server
- **Server**: Waits for incoming connections (like a restaurant waiting for customers)
- **Client**: Initiates connections (like you going to a restaurant)

### 4. Socket Communication Steps

#### For a Server:
1. **Create** a socket
2. **Bind** it to an address and port
3. **Listen** for incoming connections
4. **Accept** a connection from a client
5. **Send/Receive** data
6. **Close** the connection

#### For a Client:
1. **Create** a socket
2. **Connect** to a server
3. **Send/Receive** data
4. **Close** the connection

---

## Your Code Explained

### Overview
You've created a `SimpleSocket` class that serves as a foundation for creating network sockets. This is a **base class** (like a template) that other classes will build upon.

### File Structure

```
Networking/
├── SimpleSocket.hpp    (Header file - declarations)
└── SimpleSocket.cpp    (Implementation file - actual code)
```

---

## Function and Parameter Details

### The Constructor: `SimpleSocket(...)`

```cpp
SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
```

This is the **constructor** - it runs automatically when you create a new `SimpleSocket` object. It sets up all the necessary configurations for your socket.

#### Parameters Explained:

#### 1. **`domain`** (Address Family)
   - **What it is**: Specifies which "language" or protocol family the socket will use
   - **Common values**:
     - `AF_INET` = IPv4 addresses (like 192.168.1.1)
     - `AF_INET6` = IPv6 addresses (newer, longer addresses)
   - **Real-world analogy**: Choosing whether to use landline or mobile phone system

#### 2. **`service`** (Socket Type)
   - **What it is**: Defines how data will be transmitted
   - **Common values**:
     - `SOCK_STREAM` = TCP (reliable, ordered delivery - like registered mail)
     - `SOCK_DGRAM` = UDP (fast but unreliable - like regular mail)
   - **Real-world analogy**: Choosing between certified mail (TCP) or regular mail (UDP)

#### 3. **`protocol`**
   - **What it is**: Specifies the exact protocol to use
   - **Common values**:
     - `0` = Let the system choose the default protocol for the service type
     - `IPPROTO_TCP` = Force TCP
     - `IPPROTO_UDP` = Force UDP
   - **Usually**: Just use `0` and let the system decide

#### 4. **`port`**
   - **What it is**: A number (0-65535) that identifies which application/service to connect to
   - **Common ports**:
     - `80` = HTTP (websites)
     - `443` = HTTPS (secure websites)
     - `22` = SSH (secure remote login)
     - `3306` = MySQL database
   - **Real-world analogy**: Like an apartment number in a building (the IP address is the building)

#### 5. **`interface`** (IP Address)
   - **What it is**: The IP address to bind to or connect to
   - **Common values**:
     - `INADDR_ANY` (usually `0`) = Accept connections from any network interface
     - Specific IP like `127.0.0.1` (localhost - your own computer)
   - **Real-world analogy**: The street address of the building

---

### Inside the Constructor: Line by Line

```cpp
address.sin_family = domain;
```
- **What it does**: Sets the address family (IPv4, IPv6, etc.)
- **`sin_family`** = "socket internet family"
- **Example**: Setting it to `AF_INET` means "use IPv4 addresses"

---

```cpp
address.sin_port = htons(port);
```
- **What it does**: Sets the port number
- **`sin_port`** = "socket internet port"
- **`htons()`** = "Host TO Network Short" - converts the port number to network format
  - **Why needed?**: Different computers store numbers differently (big-endian vs little-endian)
  - Network communication uses a standard format (big-endian)
  - This function ensures compatibility across different systems

---

```cpp
address.sin_addr.s_addr = htonl(interface);
```
- **What it does**: Sets the IP address
- **`sin_addr.s_addr`** = "socket internet address"
- **`htonl()`** = "Host TO Network Long" - converts the IP address to network format
  - Same reason as `htons()` but for larger numbers (IP addresses are 32-bit)

---

```cpp
sock = socket(domain, service, protocol);
```
- **What it does**: Creates the actual socket
- **Returns**: A socket file descriptor (a number that represents your socket)
  - Think of it like a ticket number at a deli counter - the system uses this number to identify your socket
- **This is the actual socket creation** - everything before was just preparation

---

```cpp
connection = connect_to_network();
```
- **What it does**: Attempts to establish a connection or bind to an address
- **Note**: This is a **pure virtual function** (explained below)
- **Different implementations** for clients vs servers:
  - **Client**: Connects to a remote server
  - **Server**: Binds to a local address to listen for connections

---

### The Virtual Function: `connect_to_network()`

```cpp
virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
```

#### What is a Virtual Function?
- A function that **derived classes must implement**
- Allows different behavior for different types of sockets

#### Why `= 0` (Pure Virtual)?
- Makes `SimpleSocket` an **abstract class** - you cannot create it directly
- Forces child classes (like `ClientSocket` or `ServerSocket`) to provide their own implementation
- **Analogy**: Like a template with blanks that must be filled in

#### Why is this useful?
- **Clients** need to **connect** to a server → will implement `connect()`
- **Servers** need to **bind** to an address and **listen** → will implement `bind()` and `listen()`
- This design allows one base class to support both behaviors

---

## How It All Works Together

### Example Flow (Client Socket):

```
1. Create SimpleSocket object
   ↓
2. Constructor runs:
   - Sets up address structure (family, port, IP)
   - Creates socket file descriptor
   - Calls connect_to_network() → connects to server
   ↓
3. Connection established!
   ↓
4. Ready to send/receive data
```

### Example Flow (Server Socket):

```
1. Create SimpleSocket object
   ↓
2. Constructor runs:
   - Sets up address structure (family, port, IP)
   - Creates socket file descriptor
   - Calls connect_to_network() → binds to address and listens
   ↓
3. Waiting for clients to connect
   ↓
4. Accept client connections and communicate
```

---

## Key Data Structures

### `struct sockaddr_in`
This structure holds all the information about an address:

```cpp
struct sockaddr_in {
    short sin_family;        // Address family (AF_INET)
    unsigned short sin_port; // Port number (in network byte order)
    struct in_addr sin_addr; // IP address
    char sin_zero[8];        // Padding (unused)
};
```

**Think of it as**: An envelope with the complete mailing address

---

## Common Network Byte Order Functions

### Why do we need these?
Different computer architectures store multi-byte numbers differently:
- **Big-endian**: Most significant byte first (network standard)
- **Little-endian**: Least significant byte first (common on Intel processors)

### Functions:
- **`htons()`** - Host TO Network Short (for 16-bit values like ports)
- **`htonl()`** - Host TO Network Long (for 32-bit values like IP addresses)
- **`ntohs()`** - Network TO Host Short (reverse of htons)
- **`ntohl()`** - Network TO Host Long (reverse of htonl)

**Memory trick**: "h" = host, "n" = network, "s" = short, "l" = long

---

## Namespace: HDE

```cpp
namespace HDE {
    // Your code here
}
```

**What is a namespace?**
- A way to organize code and avoid naming conflicts
- Like putting your code in a folder labeled "HDE"
- **Usage**: `HDE::SimpleSocket mySocket(...);`

**Why use it?**
- Prevents name collisions (if someone else also has a `SimpleSocket` class)
- Organizes related classes together
- Professional practice in C++

---

## Next Steps

To use this `SimpleSocket` class, you would typically:

1. **Create derived classes**:
   ```cpp
   class ClientSocket : public SimpleSocket {
       int connect_to_network(int sock, struct sockaddr_in address) override {
           return connect(sock, (struct sockaddr*)&address, sizeof(address));
       }
   };
   
   class ServerSocket : public SimpleSocket {
       int connect_to_network(int sock, struct sockaddr_in address) override {
           bind(sock, (struct sockaddr*)&address, sizeof(address));
           return listen(sock, 10); // 10 = max connection queue
       }
   };
   ```

2. **Use the derived classes**:
   ```cpp
   // Create a client that connects to localhost:8080
   ClientSocket client(AF_INET, SOCK_STREAM, 0, 8080, INADDR_LOOPBACK);
   
   // Create a server that listens on port 8080
   ServerSocket server(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY);
   ```

---

## Common Issues and Notes

### Issue in Current Code
In `SimpleSocket.cpp` line 8:
```cpp
connection = connect_to_network();
```

**Problem**: Missing parameters. Should be:
```cpp
connection = connect_to_network(sock, address);
```

### Also in Header File (line 15)
```cpp
SimpleSocket(int domain,int service int protocol,int port,u_long interface);
```

**Problem**: Missing comma between `service` and `int`. Should be:
```cpp
SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
```

---

## Glossary

- **Socket**: Communication endpoint for sending/receiving data
- **Port**: Number identifying a specific service (0-65535)
- **IP Address**: Unique identifier for a computer on a network
- **Bind**: Associate a socket with a specific port and IP address
- **Listen**: Wait for incoming connections (server)
- **Connect**: Establish connection to a server (client)
- **Accept**: Accept an incoming connection (server)
- **TCP**: Transmission Control Protocol - reliable, connection-oriented
- **UDP**: User Datagram Protocol - fast, connectionless
- **File Descriptor**: Integer that identifies an open file/socket
- **Network Byte Order**: Standard format for transmitting numbers over network (big-endian)
- **Abstract Class**: Class that cannot be instantiated directly
- **Pure Virtual Function**: Function that must be implemented by derived classes

---

## Additional Resources

To learn more about socket programming:
- **Beej's Guide to Network Programming** (free online guide)
- **UNIX Network Programming** by W. Richard Stevens (comprehensive book)
- **man pages**: `man 2 socket`, `man 2 bind`, `man 2 connect` (on Linux/Unix)

---

## Summary

Your `SimpleSocket` class provides a foundation for creating network sockets. It:
1. ✅ Handles basic socket configuration (address, port, protocol)
2. ✅ Creates the socket file descriptor
3. ✅ Provides a flexible design for both client and server implementations
4. ✅ Uses proper network byte ordering
5. ✅ Follows object-oriented design principles with virtual functions

This is a solid start for building a complete networking library!
