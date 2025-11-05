# CCN Chat (server & client)

This folder contains a simple multi-client chat server and an interactive client.

Features
- Multiple simultaneous clients (each client sends a username when connecting).
- Broadcast messages and direct/multicast messages using `@username` tokens or comma-separated lists.

- Server operator can run commands on the server terminal (see below).
- Inactivity timeout (server disconnects clients after X minutes of inactivity).
- Server logs joins, disconnects, received messages, DMs, multicasts, and per-recipient sends to stdout.

Building

Use the included Makefile from the `CCN/` folder to build both programs. It links pthreads automatically.

```bash
cd CCN
make        # builds 'server' and 'client' binaries
make server # build only the server
make client # build only the client
make clean  # remove binaries
```

Server usage

```bash
./server [port] [timeout_minutes]
```

- port: TCP port to listen on (default: 8080)
- timeout_minutes: inactivity timeout in minutes (default: 2)

Server interactive commands (type into server terminal):
- `/list` — print connected users
- `/close <username>` — forcibly disconnect a user
- `@username <message>` — send a private message to a user from the server
- `/quit` — shut down the server and disconnect all clients (closes listening socket)

Message routing on the server
- Direct/multicast message formats supported from clients:
  - `@alice Hello` — DM to alice
  - `@alice @bob Hello` — send to alice and bob
  - `@alice,bob Hello` — send to alice and bob (comma-separated)

Server logs
- When users join or leave the server, the server prints alerts (e.g. `[server] ALERT: alice joined`).
- The server prints logs for message passing:
  - `[JOIN] username (sock N)` when a user joins
  - `[RX] from username (sock N) : message` when the server receives a message
  - `[DM]` and `[MCAST]` entries when direct/multicast messages are delivered
  - `[BCAST]` when a broadcast is initiated
  - `[SENT] to username (sock M) : message` for each recipient that receives data

Client usage

```bash
./client [server_ip] [port] [timeout_minutes]
```

- server_ip: IP address of the server (default: 127.0.0.1)
- port: server port to connect to (default: 8080)
- timeout_minutes: local client inactivity timeout (default: 2). When reached the client will close the connection.

Client commands and message formats
- When connecting the client prompts for a username; the client sends this username as the first message.
- Type a message and press Enter to send a broadcast to all users.
- Direct/multicast message examples (client sends these strings to the server):
  - `@bob Hey Bob` — private message to bob
  - `@alice @bob Hello` — private message to alice and bob
  - `@alice,bob Hello` — same as above
- `/list` — request the server to return the list of connected users
- `/quit` — disconnect from the server and exit the client

Examples

Start server on default port:

```bash
cd CCN
./server
```

Start a client and connect locally:

```bash
cd CCN
./client
Enter username: alice
alice: Hello everyone
@bob Hi Bob
```

Notes and limitations
- This is a simple educational example. Message framing is line-based and assumes interactive usage; production systems should use length-prefixed framing or a higher-level protocol (e.g., WebSocket).
- The server uses one detached thread per client. For large-scale usage, consider an event-driven approach or a thread-pool.
- Logs are printed to stdout; you can redirect output to a file when launching the server for persistent logging.

License & attribution
- This code is a small lab/example — adapt it to your needs.
# CCN Chat (server & client)

This folder contains a simple multi-client chat server and an interactive client.

Features
- Multiple simultaneous clients (each client sends a username when connecting).
- Broadcast messages and direct messages using `@username` prefix.
- Server operator can run commands on the server terminal (see below).
- Inactivity timeout (server disconnects clients after X minutes of inactivity).
- Server logs joins, disconnects, received messages, DMs, and per-recipient sends to stdout.

Building

Compile with g++ and pthreads (examples used during development):

```bash
g++ -std=c++11 CCN/server.cpp -o CCN/server -pthread
g++ -std=c++11 CCN/client.cpp -o CCN/client -pthread
```

Server usage

```bash
./CCN/server [port] [timeout_minutes]
```

- port: TCP port to listen on (default: 8080)
- timeout_minutes: inactivity timeout in minutes (default: 2)

Server interactive commands (type into server terminal):
- `/list` — print connected users
- `/close <username>` — forcibly disconnect a user
- `@username <message>` — send a private message to a user from the server
- `/quit` — shut down the server and disconnect all clients

Server logs
- When users join or leave the server, the server prints alerts (e.g. `[server] ALERT: alice joined`).
- The server prints logs for all message passing:
  - `[JOIN] username (sock N)` when a user joins
  - `[RX] from username (sock N) : message` when the server receives a message
  - `[DM] from sender (sock N) to target (sock M) : body` when a DM is delivered
  - `[BCAST] from sender (sock N) : message` when a broadcast is initiated
  - `[SENT] to username (sock M) : message` for each recipient that receives data

Client usage

```bash
./CCN/client [server_ip] [port] [timeout_minutes]
```

- server_ip: IP address of the server (default: 127.0.0.1)
- port: server port to connect to (default: 8080)
- timeout_minutes: local client inactivity timeout (default: 2). When reached the client will close the connection.

Client commands and message formats
- When connecting the client prompts for a username; the client sends this username as the first message.
- Type a message and press Enter to send a broadcast to all users.
- Direct message: start your message with `@username` followed by a space and the message body.
  - Example: `@bob Hey Bob` sends a private message to `bob`.
- `/list` — request the server to return the list of connected users
- `/quit` — disconnect from the server and exit the client