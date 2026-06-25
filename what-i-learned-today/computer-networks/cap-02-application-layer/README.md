# Computer Networks — Ch. 2 (Kurose & Ross): The Application Layer

Study notes for **Chapter 2** of *Computer Networking: A Top-Down
Approach* (Kurose & Ross).

> Scope of these notes: **Section 2.1 — Principles of Network
> Applications** only (up to, but not including, *2.2 Web and HTTP*).

---

## Network Application Architectures

The **application architecture** is designed by the developer and dictates
how the app is structured over the end systems. It is **different** from
the *network architecture* (the fixed 5-layer stack). Two dominant
paradigms:

### 1. Client-Server Architecture

There is an always-on host, the **server**, that services requests from
many other hosts, the **clients**.

```
        ┌──────────┐
  Client│          │
   ─────▶          │
        │  Server  │◀───── Client
        │ (always  │
   ─────▶   on)    │◀───── Client
  Client│          │
        └──────────┘
```

- The server has a **fixed, well-known IP address** so clients can always
  reach it.
- **Clients do not communicate directly** with each other.
- A single server can be overwhelmed → providers use **data centers** with
  large numbers of hosts to create a powerful *virtual server*.
- Examples: Web, FTP, Telnet, e-mail.

### 2. Peer-to-Peer (P2P) Architecture

Minimal (or no) reliance on dedicated servers. Instead, the application
exploits **direct communication between pairs of intermittently connected
hosts** called **peers** (e.g., users' own laptops/desktops).

```
 [Peer]◀────▶[Peer]
    ▲   ╲    ╱   ▲
    │    ╲  ╱    │
    ▼     ╳      ▼
 [Peer]◀─╱──╲──▶[Peer]
```

- **Self-scalability**: each peer adds service capacity (by serving others)
  as well as load. New peers bring new resources.
- **Cost-effective**: little server infrastructure / bandwidth needed.
- Examples: BitTorrent (file distribution), P2P telephony.
- **Challenges**: security, performance, and reliability are harder because
  of the highly **distributed and decentralized** structure. ISPs are also
  designed for "download-heavy" residential use, which P2P upload-heavy
  traffic stresses.

> Some applications are **hybrid** — e.g., many messaging apps use servers
> to track users' addresses but let users exchange messages directly.

---

## Processes Communicating

Within the OS, the program in execution is a **process**. When processes
run on the **same** host they communicate via inter-process communication
(governed by the OS). We care about processes on **different** hosts, which
communicate by **exchanging messages** across the network.

### Client and Server Processes

For each pair of communicating processes, one is labeled the **client** and
the other the **server**:

> The process that **initiates** the communication (the one that first
> contacts the other) is the **client**. The process that **waits to be
> contacted** is the **server**.

This holds even in P2P: within a single file transfer, the peer that
*requests* the file acts as the client, while the peer that *sends* it acts
as the server. A peer can be **both** client and server over time.

### The Socket Interface

A process sends/receives messages through a software interface called a
**socket** — the **door** between the application process and the network.

```
   Host (sender)                        Host (receiver)
┌──────────────────┐                ┌──────────────────┐
│  Application      │                │  Application      │
│   process         │                │   process         │
│      │ socket     │                │   socket │        │
│      ▼ ┌────┐     │   Internet     │   ┌────┐ ▼        │
│        │door│─────┼───────────────▶┼──▶│door│          │
│  Transport-Link-  │  (controlled   │  Transport-Link-  │
│  Physical layers  │   by the OS)   │  Physical layers  │
└──────────────────┘                └──────────────────┘
```

- The socket is the **API between the application and the network** — the
  application layer sits on the app side of the door; everything below is
  controlled by the OS.
- The developer controls **everything on the application-layer side** of the
  socket, but has **little control** over the transport-layer side (only the
  choice of transport protocol and a few parameters such as buffer/segment
  sizes).

### Addressing Processes

To deliver a message to the right process on the right host, two pieces of
information are needed:

1. The **address of the host** — its **IP address** (a 32-bit value in
   IPv4).
2. An identifier for the **receiving process** (more precisely, the
   receiving socket) on that host — the **port number**.

Popular applications use **well-known port numbers**, e.g.:
- **HTTP → port 80**
- **SMTP (mail) → port 25**

---

## Transport Services Available to Applications

The socket is the interface between the app and the transport-layer
protocol. When you build an app, you must choose a transport protocol. The
services a transport protocol can offer fall into **four dimensions**:

| Dimension | Question it answers |
|---|---|
| **Reliable data transfer** | Will every byte arrive, intact and complete? |
| **Throughput** | Is a guaranteed minimum bit rate available? |
| **Timing** | Are delivery-delay guarantees provided? |
| **Security** | Are encryption / data-integrity services provided? |

### 1. Reliable Data Transfer

Some apps (e-mail, file transfer, web docs, financial apps) are
**loss-intolerant** — data must arrive **correctly and completely**. A
transport protocol that guarantees this provides **reliable data transfer**.

Other apps are **loss-tolerant** — e.g., audio/video, where occasional lost
data causes only a minor glitch. These can use a protocol **without**
reliable delivery.

### 2. Throughput

The rate at which the sending process can deliver bits to the receiving
process. Because other sessions share the links, available throughput
fluctuates.

- **Bandwidth-sensitive applications** need a **guaranteed minimum
  throughput** (e.g., many multimedia apps). A protocol could reserve a
  required rate `r` bits/sec.
- **Elastic applications** make use of *whatever* throughput is available
  (e.g., e-mail, file transfer, web) — more is nice, but not required.

### 3. Timing

A transport protocol could offer **timing guarantees** — e.g., "every bit
the sender pumps in arrives at the receiver within 100 ms." Useful for
**real-time, interactive** applications: telephony, gaming,
teleconferencing, virtual environments.

### 4. Security

A transport protocol can provide **security services**:
- **Encryption** of all transmitted data (confidentiality), so a sniffer
  cannot read it.
- **Data integrity** and **end-point authentication**.

---

## Transport Services Provided by the Internet

The Internet (TCP/IP) makes **two** transport protocols available to
applications: **TCP** and **UDP**. The developer picks one when creating
the sockets. Here is what each offers against the four dimensions above.

### TCP Services

- **Connection-oriented**: a **handshake** is performed before app messages
  flow, establishing a **full-duplex** TCP connection between the two
  processes' sockets. The connection is torn down when finished.
- **Reliable data transfer**: delivers all data **without error and in the
  correct order** — no missing or duplicate bytes.
- **Congestion control**: throttles a sending process when the network is
  congested. It works for the *general good* of the Internet rather than the
  direct benefit of the communicating processes.

> TCP does **not** provide **throughput, timing, or security** guarantees.

**TLS (securing TCP):** because plain TCP has no encryption, **TLS** (a
security enhancement built **at the application layer**, on top of TCP)
provides encryption, data integrity, and end-point authentication. TLS is
**not** a third Internet transport protocol — it lives in the application,
with the app's data passing through TLS before going into the TCP socket.

### UDP Services

- **Connectionless**: **no handshake** beforehand.
- **Unreliable data transfer**: no guarantee a message arrives, and
  messages may arrive **out of order**.
- **No congestion control**: a sending process can pump data at any rate it
  likes (though it may not all get through).

UDP is **lightweight / bare-bones**. It also provides **no** throughput,
timing, or security guarantees.

### What the Internet Transport Protocols Do *Not* Provide

Notably, **neither TCP nor UDP offers throughput or timing guarantees**.
Today's Internet can often serve time-sensitive apps *well enough*, but it
makes **no promises**. Application designers cope by designing around this —
e.g., buffering, adaptive bit rates, and over-provisioned/ private networks
(CDNs) — rather than relying on transport-layer guarantees that don't exist.

#### Common Applications and Their Transport Protocols

| Application | App-layer protocol | Underlying transport |
|---|---|---|
| E-mail | SMTP | TCP |
| Remote terminal access | Telnet / SSH | TCP |
| Web | HTTP, HTTP/3* | TCP (HTTP/3 over UDP) |
| File transfer | FTP | TCP |
| Streaming multimedia | HTTP, DASH | TCP |
| Internet telephony | SIP, RTP, proprietary | UDP **or** TCP |

\* HTTP/3 runs over QUIC, which itself runs over UDP.

---

## Application-Layer Protocols

An **application-layer protocol** defines how an application's processes,
running on different end systems, pass messages to each other. It specifies:

1. The **types of messages** exchanged (e.g., request and response).
2. The **syntax** of each message type — which fields it has and how they
   are delineated.
3. The **semantics** of the fields — the meaning of the information.
4. **Rules** for when and how a process sends and responds to messages.

> **Network application ≠ application-layer protocol.** The protocol is just
> **one piece** of a network application. Example: the **Web** is an
> application that includes a document format (HTML), browsers, web servers,
> and **HTTP** — and HTTP is *only* the protocol part.

Some protocols are in the **public domain** (specified in **RFCs**, so
anyone can build an interoperable implementation — e.g., HTTP). Others are
**proprietary** and deliberately not published.

---

## Key Takeaways

- Network applications run **only on end systems** — never on the network
  core — which is why new apps can be built and deployed so quickly.
- Two main **application architectures**: **client-server** (always-on
  server with a fixed IP, clients don't talk to each other) and **P2P**
  (intermittently connected peers; **self-scaling**, cheap, but harder to
  secure/manage). Hybrids exist.
- **Processes communicate by exchanging messages through sockets**; the
  process that *initiates* contact is the **client**, the one that *waits*
  is the **server**.
- A process is addressed by an **(IP address, port number)** pair; popular
  apps use **well-known ports** (HTTP 80, SMTP 25).
- A transport service can be characterized along **four dimensions**:
  **reliable data transfer, throughput, timing, and security**.
- The Internet offers **TCP** (connection-oriented, reliable, congestion-
  controlled) and **UDP** (connectionless, unreliable, no congestion
  control). **Neither guarantees throughput or timing.** **TLS** adds
  security on top of TCP, at the application layer.
- An **application-layer protocol** defines message types, their syntax and
  semantics, and the rules for exchanging them — it is **only one component**
  of a full network application.

---

## Further Reading

- *Computer Networking: A Top-Down Approach* — Kurose & Ross
  (Ch. 2.1: Principles of Network Applications)
- [RFC 2616 / RFC 7230 — HTTP](https://www.rfc-editor.org/rfc/rfc7230) *(for §2.2, next)*
