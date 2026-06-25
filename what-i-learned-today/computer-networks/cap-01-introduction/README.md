# Computer Networks — Ch. 1 (Kurose & Ross): The Internet and Its Fundamentals

Study notes for **Chapter 1** of *Computer Networking: A Top-Down
Approach* (Kurose & Ross).

---

## What Is the Internet?

The book presents two complementary views.

### 1. The "nuts and bolts" view

The Internet is a network of networks, connecting billions of
**end systems** (hosts) through **communication links** and
**packet switches** (routers and switches).

```
[Host A] --link-- [Router] --link-- [Router] --link-- [Host B]
                      |                  |
                  [Router]           [Router]
                      |                  |
                   [Host C]           [Host D]
```

- **Hosts / end systems**: PCs, smartphones, servers, IoT devices.
- **Communication links**: copper, fiber, radio, satellite — each with a
  **transmission rate (bandwidth)**, measured in bits/sec.
- **Packet switches**: take a packet arriving on one input link and
  forward it on an output link (routers in the network core, switches in
  access networks).
- **Routes/paths**: the sequence of links and packet switches traveled by
  a packet from sender to receiver.

All of this runs under **protocols** — rules that govern how information
is sent and received. The two most important Internet protocols are
**TCP** and **IP** (the **TCP/IP** stack).

### 2. The services view (infrastructure for applications)

The Internet can also be seen as **infrastructure that provides services
to distributed applications**: the web, e-mail, streaming, social
networks, online gaming, VoIP, etc.

Applications use the **socket API**, which defines:
- how a program running on one end system asks the network
  infrastructure to deliver data to another program running on another
  end system.
- this is analogous to the rules of the postal service: you place a
  letter in an envelope, write the address, and the postal service
  (network) handles the rest.

---

## The Network Edge

The **edge** is where hosts live — divided into:

| Role | Description | Examples |
|---|---|---|
| **Client** | Typically desktops/mobile, often intermittently connected, initiate requests | Browser, chat app |
| **Server** | More powerful, always-on, often in data centers | Web servers, mail servers |

### Access Networks

The link that connects an end system to the first router (**edge
router**) on its path to any other distant host.

```
User's home                    ISP
┌─────────┐  access   ┌──────────────┐    Internet
│  Host   │──────────▶│ Edge Router  │───▶  core
└─────────┘           └──────────────┘
```

Main access technologies:

- **DSL (Digital Subscriber Line)**: reuses existing telephone wiring,
  with a *splitter* separating data and voice.
- **Cable (Cable / HFC)**: reuses the cable TV provider's infrastructure;
  a **shared** medium — multiple homes share the same link up to the
  cable head-end.
- **FTTH (Fiber to the Home)**: optical fiber running directly to the
  residence, offering higher rates.
- **Mobile networks (3G/4G/5G)**: wireless access via base stations.
- **Enterprise/home access networks**: Ethernet and Wi-Fi (LANs).

---

## The Network Core

The core is the mesh of routers interconnecting the end systems. Two
fundamental approaches to moving data:

### Packet Switching

Data is broken into **packets**, each sent independently and
stored/forwarded by each router along the path.

```
Message → [P1][P2][P3][P4]   (each packet has a header + payload)

Host A → Router 1 → Router 2 → Host B
```

**Store-and-forward**: a router only begins transmitting a packet after
it has **received the entire packet**.

```
Transmission delay for an L-bit packet on a link with rate R:
   delay = L / R
```

**Queuing and packet loss**: if packets arrive faster than the output
link can transmit them, they wait in a **buffer (queue)**. If the buffer
fills up, packets are **dropped (packet loss)**.

```
        router's buffer
arrive ──▶[▮▮▮▮▮▮▮▮░░]──▶ depart
              ↑
         if full → packet dropped
```

**Forwarding vs. routing**:
- *forwarding*: a router's local action — moving a packet from an input
  link to the correct output link, using its **forwarding table**.
- *routing*: the global process, carried out by routing algorithms, that
  determines the values in those tables across the whole network.

### Circuit Switching

Used in traditional telephone networks. Link resources (bandwidth) are
**reserved** for the connection for the entire duration of the call.

| | Packet switching | Circuit switching |
|---|---|---|
| Resources | Shared (on demand) | Dedicated/reserved |
| Performance guarantees | No (best-effort) | Yes |
| Efficiency | High (statistical multiplexing) | May waste idle resources |
| Example | Internet | Traditional telephone network |

**Multiplexing in circuit switching**:
- **FDM (Frequency-Division Multiplexing)**: divides the spectrum into
  frequency bands, one per connection.
- **TDM (Time-Division Multiplexing)**: divides time into repeating
  *slots*, one per connection.

### Networks of Networks

The Internet is a hierarchy of interconnected **ISPs**: access ISPs
(Tier 3) connect to regional ISPs, which connect to **Tier-1 ISPs**
(global backbones), along with **Internet Exchange Points (IXPs)** and
**content provider networks** (Google, Netflix, Meta, etc., each with
their own backbones).

---

## Delay, Loss, and Throughput

### The Four Sources of Delay

For a packet to travel from one node to another, it experiences:

```
┌────────────┬─────────┬──────────────┬─────────────┐
│ Processing │  Queuing │ Transmission │ Propagation │
└────────────┴─────────┴──────────────┴─────────────┘
```

| Type | What it is | Depends on |
|---|---|---|
| **Processing (d_proc)** | Time to examine the header and determine where to send the packet | Router speed |
| **Queuing (d_queue)** | Time spent waiting in the output buffer | Congestion (variable!) |
| **Transmission (d_trans)** | Time to push all the packet's bits onto the link | `L / R` (packet length / link rate) |
| **Propagation (d_prop)** | Time for the signal to travel through the physical medium | `distance / propagation speed` |

**Total nodal delay**:
```
d_nodal = d_proc + d_queue + d_trans + d_prop
```

> Transmission ≠ Propagation: transmission is "pushing the bits out the
> door"; propagation is "how long the signal takes to travel to the
> other end."

### Queuing Delay and Packet Loss

Queuing delay depends on the **traffic intensity** `La/R`, where:
- `L` = packet length, `a` = packet arrival rate, `R` = link rate.

```
La/R → 0   : small queuing delay
La/R → 1   : queuing delay grows, tends toward infinity
La/R > 1   : queue grows without bound → buffer fills → packet loss
```

### Throughput

The rate (bits/time) at which bits are transferred between sender and
receiver. Across a network with multiple links in series, end-to-end
throughput is limited by the **link with the smallest capacity** (the
"bottleneck"):

```
Host A --10Mbps--▶ R1 --1Mbps--▶ R2 --10Mbps--▶ Host B

End-to-end throughput = min(10, 1, 10) Mbps = 1 Mbps  (bottleneck)
```

---

## Protocol Layers

Networks are complex systems — the solution is to **organize them into
layers**, where each layer provides **services** to the layer above,
implementing them based on services received from the layer below.

### The Internet's 5-Layer Model

```
┌─────────────────┐
│   Application    │  HTTP, SMTP, DNS, ...        → messages
├─────────────────┤
│   Transport      │  TCP, UDP                    → segments
├─────────────────┤
│   Network        │  IP, routing protocols       → datagrams
├─────────────────┤
│   Link           │  Ethernet, Wi-Fi              → frames
├─────────────────┤
│   Physical       │  bits on the transmission medium
└─────────────────┘
```

| Layer | Responsibility | Data unit (PDU) |
|---|---|---|
| Application | Supports network applications | Message |
| Transport | Process-to-process data transfer | Segment |
| Network | Routing of datagrams from source to destination | Datagram |
| Link | Data transfer between neighboring nodes | Frame |
| Physical | Transmission of bits "on the wire" | Bit |

### The OSI Model (7 Layers)

The OSI model adds two layers between Application and Transport:

```
Application ─ Presentation ─ Session ─ Transport ─ Network ─ Link ─ Physical
```
- **Presentation**: allows applications to interpret exchanged data
  (e.g., compression, encryption, encoding).
- **Session**: data synchronization, checkpointing, and recovery.

In practice, the Internet uses the **5-layer model** — presentation and
session functionality is handled by the application itself, when needed.

### Encapsulation

Each layer adds its own header (and sometimes trailer) to the data
received from the layer above:

```
Application: [        M        ]
Transport:   [Ht|        M        ]
Network:     [Hn|Ht|        M        ]
Link:        [Hl|Hn|Ht|        M        ]

M  = application message
Ht = transport-layer header (e.g., TCP/UDP port numbers)
Hn = network-layer header (e.g., IP addresses)
Hl = link-layer header (e.g., MAC addresses)
```

At a router, only the **physical, link, and network** layers are
processed — the router never "opens" the transport segment or the
application message.

---

## A Brief History of the Internet

- **1961-1972** — Foundations of packet switching; ARPANET (1969).
- **1972-1980** — Proprietary networks and internetworking; TCP and IP
  are born.
- **1980-1990** — Proliferation of networks; the Internet as we know it
  emerges, with DNS and TCP/IP officially adopted (1983).
- **1990-present** — Explosion of the web (HTTP, browsers), e-commerce,
  social networks, streaming, mobile, and IoT.

---

## Key Takeaways

- The Internet can be viewed as **infrastructure** (hosts, links, packet
  switches) or as a **service platform** for distributed applications
  (via the socket API).
- The **network edge** contains the hosts (clients/servers) and the
  **access networks** (DSL, cable, fiber, mobile, LAN).
- The **network core** mainly uses **packet switching**
  (store-and-forward, queuing, forwarding/routing), as opposed to the
  **circuit switching** (FDM/TDM) used in traditional telephony.
- End-to-end delay = sum of **4 delays per node**: processing, queuing,
  transmission, and propagation — queuing is the only variable one
  (depends on traffic).
- **End-to-end throughput** is limited by the smallest-capacity link
  (the "bottleneck") along the path.
- The **layered architecture** (5 layers in the Internet, 7 in OSI)
  organizes complexity: each layer offers services to the layer above
  using services from the layer below.
- **Encapsulation**: each layer adds its own header to the data received
  from the layer above, forming that layer's PDU.

---

## Further Reading

- *Computer Networking: A Top-Down Approach* — Kurose & Ross
  (Ch. 1: Computer Networks and the Internet)
- [RFC 1180 — A TCP/IP Tutorial](https://www.rfc-editor.org/rfc/rfc1180)
