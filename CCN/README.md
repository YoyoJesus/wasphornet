# CCN Lab 1 (server & client)

## Features

- Multiple simultaneous clients (each client sends a username when connecting).
- Broadcast messages and direct/multicast messages using `@username` tokens or comma-separated lists.
- Server operator can run commands on the server terminal (see below).
- Inactivity timeout (server disconnects clients after 2 minutes of inactivity). The server enforces inactivity timeouts centrally; clients do not perform local inactivity disconnects.
- Server logs joins, disconnects, received messages, DMs, multicasts, and per-recipient sends to stdout.

## Building

Use the included Makefile to build both programs. It links pthreads automatically.

```bash
cd CCN
make all    # builds 'server' and 'client' binaries
make clean  # remove binaries
```

## Server usage

```bash
./server
```

### Server interactive commands (type into server terminal)

- Type a message and press Enter to send a broadcast to all users.
 - `/list` — print connected users
 - `/dump_activity` — print tracked activity entries (username or socket and seconds since last activity)
 - `/close <username>` — forcibly disconnect a user
 - `@username <message>` — send a private message to a user from the server
 - `/shutdown` — shut down the server and disconnect all clients (terminates the server process)

### Message routing on the server

Direct/multicast message formats supported from clients:

- `@alice Hello` — DM to alice
- `@alice @bob Hello` — send to alice and bob
- `@alice,bob Hello` — send to alice and bob (comma-separated)

Usernames must be unique among connected clients. If a username is already taken, the server will reply with `USERNAME_TAKEN` and the client will be prompted to choose a different name.

### Server logs

- When users join or leave the server, the server prints alerts (e.g. `[server] ALERT: alice joined`).
- The server prints logs for message passing:
  - `[JOIN] username (sock N)` when a user joins
  - `[RX] from username (sock N) : message` when the server receives a message
  - `[DM]` and `[MCAST]` entries when direct/multicast messages are delivered
  - `[BCAST]` when a broadcast is initiated
  - `[SENT] to username (sock M) : message` for each recipient that receives data
  - `[TIMEOUT]` when a client times out due to inactivity

## Client usage

```bash
./client
```

### Client commands and message formats

- When connecting the client prompts for a username; the client sends this username as the first message.
- Type a message and press Enter to send a broadcast to all users.
- Direct/multicast message examples (client sends these strings to the server):
  - `@bob Hey Bob` — private message to bob
  - `@alice @bob Hello` — private message to alice and bob
  - `@alice,bob Hello` — same as above
- `/list` — request the server to return the list of connected users
- `/quit` — disconnect from the server and exit the client
- `/shutdown <password>` — request the server shut down; requires the server password (default is `admin123` in this build). If authorized, the server will terminate.

### Examples

Start a client and connect locally:

```bash
./client
Enter username: alice
alice: Hello everyone
@bob Hi Bob
```

Send a multicast message on the client side:

```bash
@bob,joe Hello!

OR

@bob @jim Hello!
```

Shutdown server from client side:

```bash
/shutdown admin123

[SERVER] Shutdown authorized
[SERVER] Server is shutting down
initiated by guest559 with elevated permissions
```