# Computer Networks — Ch. 1 (Kurose & Ross): Review Questions

Solutions to the **Review Questions** from Chapter 1 of *Computer
Networking: A Top-Down Approach* (Kurose & Ross).

---

# Section 1.1

## R1. What is the difference between a host and an end system? List the types of end systems. Is a Web server an end system?

There is **no difference** — the terms *host* and *end system* are used
**interchangeably** in the book. Both refer to the devices connected at
the **edge** of the network that run the applications (they are not the
packet switches in the core).

**Types of end systems** include:

- Desktop and laptop PCs
- Smartphones and tablets
- Servers (Web, mail, file servers)
- IoT / "things": Web TVs, gaming consoles, sensors, smart-home devices,
  cars, etc.

**Yes — a Web server is an end system.** It sits at the edge of the
network and runs an application (the Web server program), so it is a host
just like any client device.

---

## R2. The word *protocol* is often used to describe diplomatic relations. How does Wikipedia describe a diplomatic protocol?

Wikipedia describes a **diplomatic protocol** as the **etiquette of
diplomacy and affairs of state** — the customary set of rules,
formalities, and procedures of conduct that are observed in official
dealings between states and their representatives.

The analogy with networking is direct: just as diplomatic protocol
defines the proper, agreed-upon way for officials to interact, a
**network protocol** defines the format and order of the messages
exchanged between communicating entities, plus the actions taken when a
message is sent or received.

---

## R3. Why are standards important for protocols?

Standards are important because they let **products and equipment from
different vendors interoperate**. A protocol only works if **all
communicating parties agree** on:

- the **format** and **order** of the messages exchanged, and
- the **actions** taken when messages are sent or received.

If every company invented its own incompatible protocol, devices could
not talk to each other and a single global network like the Internet
could not exist. Open **standards** (e.g., those published as **RFCs** by
the IETF) provide one common, public specification that everyone can
implement, guaranteeing that a host built by one manufacturer can
communicate with a host built by another.

---

# Section 1.2

## R4. List four access technologies. Classify each as residential, enterprise, or mobile access.

| Access technology | Category |
|---|---|
| **DSL** | Residential access |
| **HFC (cable)** | Residential access |
| **FTTH (fiber)** | Residential access |
| **Ethernet** | Enterprise access |
| **Wi-Fi** | Enterprise / residential access |
| **3G / 4G / 5G** | Mobile access |

(Any four of the above, correctly classified.)

---

## R5. Is the HFC transmission rate dedicated or shared among users? Are collisions possible in the downstream direction of an HFC channel? Why?

The HFC transmission rate is **shared** among users — the neighborhood's
homes share the same cable up to the cable head-end.

In the **downstream** direction (provider → user) there are **no
collisions**, because there is a **single sender** (the cable head-end)
transmitting onto the channel. Collisions can only occur in the
**upstream** direction, where multiple homes transmit on the same shared
channel.

---

## R6. List the residential access technologies available in your city, with advertised downstream rate, upstream rate, and monthly price.

*(Open-ended, depends on local providers.)* Typical example:

| Technology | Downstream | Upstream | Monthly price |
|---|---|---|---|
| FTTH (fiber) | 300–600 Mbps | 150–300 Mbps | ~R$ 100 |
| HFC (cable) | 200 Mbps | 30 Mbps | ~R$ 110 |
| DSL | 15 Mbps | 1 Mbps | ~R$ 80 |

Check your own ISPs' current plans for exact figures.

---

## R7. What is the transmission rate of Ethernet LANs?

Ethernet LANs run at a range of rates: **10 Mbps, 100 Mbps, 1 Gbps,
10 Gbps**, and higher (40/100 Gbps). Today **100 Mbps and 1 Gbps** are
the most common in homes and offices.

---

## R8. List some physical media used to deploy Ethernet.

- **Twisted-pair copper wire** (e.g., Cat 5/6 UTP)
- **Coaxial cable** (older Ethernet)
- **Fiber-optic cable** (for higher rates / longer distances)

---

## R9. HFC, DSL, and FTTH are used for residential access. For each, give a range of transmission rates and say whether the rate is shared or dedicated.

| Technology | Typical rate range | Shared or dedicated |
|---|---|---|
| **HFC** | up to ~40 Mbps down / a few Mbps up | **Shared** (neighborhood shares the cable) |
| **DSL** | ~1–50 Mbps down / hundreds of kbps–a few Mbps up | **Dedicated** (own line to the DSLAM) |
| **FTTH** | hundreds of Mbps to Gbps | **Dedicated** (depends on architecture; direct fiber is dedicated) |

---

## R10. Describe the most popular wireless access technologies today and compare them.

- **Wi-Fi (WLAN / 802.11)**: short range (tens of meters), high rates
  (tens of Mbps to Gbps). The user must be near a base station / access
  point connected to a wired network. Free to deploy, but limited
  coverage.
- **Cellular (3G/4G/5G/WWAN)**: long range (tens of km via base
  stations / cell towers), rates from a few Mbps (3G) to hundreds of Mbps
  or more (4G/5G). Provided by a telecom operator (paid), with wide-area
  coverage and mobility.

**Comparison**: Wi-Fi gives higher local throughput over a tiny area for
free; cellular gives broad mobility and coverage at lower local rates and
a subscription cost.

---

# Section 1.3

## R11. With exactly one store-and-forward packet switch between source and destination (link rates R₁ and R₂), what is the total end-to-end delay for a packet of length L? (Ignore queuing, propagation, and processing delays.)

With store-and-forward, the switch must receive the **entire** packet
before forwarding it. So the delay is the sum of the two transmission
delays:

```
d_end-to-end = L / R₁  +  L / R₂
```

---

## R12. What is the advantage of a circuit-switched network over a packet-switched one? What are the advantages of TDM over FDM in a circuit-switched network?

- **Circuit switching vs. packet switching**: a circuit-switched network
  **reserves resources** for the call, providing **guaranteed,
  constant-rate** end-to-end performance (no queuing delay, no packet
  loss from congestion).
- **TDM vs. FDM**: in TDM, each connection gets the **full bandwidth of
  the link** during its time slots, whereas FDM limits each connection to
  a narrow **frequency band** for the whole duration. TDM can therefore
  achieve higher per-connection rates.

---

## R13. Users share a 2 Mbps link; each transmits continuously at 1 Mbps but only 20% of the time.

**a.** *Circuit switching:* each user needs 1 Mbps, the link is 2 Mbps,
so **2 users** can be supported.

**b.** With packet switching, **two or fewer** users transmitting at once
require ≤ 2 Mbps, which the 2 Mbps link can carry — **no queue**. With
**three** users transmitting at once the demand is 3 Mbps > 2 Mbps, so
the queue **grows**.

**c.** Probability a given user is transmitting = **0.2**.

**d.** Probability all three transmit simultaneously
= 0.2 × 0.2 × 0.2 = **0.008 (0.8%)**. The queue grows exactly when all
three are active, so the queue grows **0.8% of the time**.

---

## R14. Why will two ISPs at the same level of the hierarchy peer? How does an IXP earn money?

Two ISPs at the same level **peer** to exchange traffic **directly**
instead of routing it through a (paid) upstream provider — this
**reduces cost** and often improves performance/latency for their
customers' traffic.

An **IXP (Internet Exchange Point)** earns money by **charging the ISPs
and content networks** that connect to it (ports / membership fees) for
the ability to interconnect at that location.

---

## R15. Some content providers built their own networks. Describe Google's network. What motivates content providers to build them?

Google operates its own **private global network**: many data centers,
clusters in IXPs, and **private high-speed fiber links** connecting them,
plus direct interconnections (peering) with access ISPs.

**Motivation**: it **bypasses the upper tiers of the Internet** (reducing
payments to transit ISPs), gives Google **more control over performance**
(lower latency, higher throughput to users), and lets it place content
**closer to end users**.

---

# Section 1.4

## R16. For a packet sent over a fixed route, list the delay components of the end-to-end delay. Which are constant and which are variable?

The four nodal delay components:

| Component | Constant or variable |
|---|---|
| **Processing delay** | (Roughly) constant |
| **Transmission delay** | Constant (= L / R) |
| **Propagation delay** | Constant (= d / s) |
| **Queuing delay** | **Variable** — depends on congestion/traffic |

Only **queuing delay** varies; the others are essentially fixed for a
given path and packet.

---

## R17. "Transmission versus Propagation Delay" animation — find a setting where the sender finishes transmitting before the first bit arrives, and another where the first bit arrives before the sender finishes.

- **Sender finishes before the first bit arrives**: choose a
  **small packet / high transmission rate** combined with a **large
  propagation delay** (long, slow link) → small `L/R`, large `d/s`.
- **First bit arrives before the sender finishes**: choose a
  **large packet / low transmission rate** combined with a **small
  propagation delay** (short link) → large `L/R`, small `d/s`.

---

## R18. How long does a 1,000-byte packet take to propagate over a 2,500 km link at 2.5 × 10⁸ m/s with a rate of 2 Mbps? Give the general formula. Does it depend on packet length or transmission rate?

**Propagation delay** = distance / propagation speed:

```
d_prop = (2,500 × 10³ m) / (2.5 × 10⁸ m/s) = 0.01 s = 10 ms
```

**General formula**: `d_prop = d / s`.

It does **not** depend on the packet length **L**, and it does **not**
depend on the transmission rate **R**. (Those affect the *transmission*
delay `L/R`, not propagation.)

---

## R19. Host A sends a large file to Host B over three links: R₁ = 500 kbps, R₂ = 2 Mbps, R₃ = 1 Mbps.

**a.** Throughput = bottleneck = `min(500 kbps, 2 Mbps, 1 Mbps)`
= **500 kbps**.

**b.** File = 4 × 10⁶ bytes = 32 × 10⁶ bits.
Time = 32 × 10⁶ bits / 500 × 10³ bps = **64 seconds**.

**c.** With R₂ reduced to 100 kbps:
- Throughput = `min(500, 100, 1000) kbps` = **100 kbps**.
- Time = 32 × 10⁶ / 100 × 10³ = **320 seconds**.

---

## R20. How does end system A turn the file into packets? When a packet reaches a router, what info does the router use to choose the outgoing link? Why is Internet packet switching like driving city-to-city asking for directions?

- **Packetizing**: A breaks the file into chunks and adds a **header** to
  each chunk, forming packets (segments → datagrams with addresses).
- **Forwarding**: the router reads the packet's **destination IP
  address** in the header and looks it up in its **forwarding table** to
  pick the outgoing link.
- **Analogy**: like a driver who asks for directions at each
  intersection, each **router independently** decides the next hop based
  on local information (its table) — there is no pre-reserved end-to-end
  route; the path is determined hop by hop.

---

## R21. "Queuing and Loss" animation — what are the max and min transmission rates? What is the traffic intensity? How long until a packet is lost? Are the results the same on repeat? Why / why not?

*(Open-ended interactive task.)* Conceptually:

- Traffic intensity = **La / R**. With the maximum arrival rate equal to
  the link rate, intensity ≈ **1**, where loss begins to occur.
- The **time until the first loss differs** on each run because packet
  **arrivals are random** — the queue fills at different moments, so the
  first drop happens at a different time even with identical rates.

---

# Section 1.5

## R22. List five tasks a layer can perform. Can one or more of these be done by two or more layers?

Example tasks a layer can perform:

1. **Error detection / correction**
2. **Flow control**
3. **Segmentation and reassembly**
4. **Multiplexing / demultiplexing**
5. **Connection setup**

**Yes** — some functions appear in **more than one layer**. For example,
error detection is done at both the link and transport layers, and
flow control exists at both the link and transport layers.

---

## R23. What are the five layers of the Internet protocol stack, and the main responsibility of each?

| Layer | Main responsibility |
|---|---|
| **Application** | Supports network applications (HTTP, SMTP, DNS) |
| **Transport** | Process-to-process data transfer (TCP, UDP) |
| **Network** | Routing of datagrams from source to destination (IP) |
| **Link** | Data transfer between neighboring network elements (Ethernet, Wi-Fi) |
| **Physical** | Moves the individual **bits** across the medium |

---

## R24. What is an application-layer message? A transport-layer segment? A network-layer datagram? A link-layer frame?

These are the **PDUs** (Protocol Data Units) — the data unit plus that
layer's header — at each layer:

- **Message**: the data an application sends (application layer).
- **Segment**: a transport-layer PDU = transport header + message
  (or part of it).
- **Datagram**: a network-layer PDU = network header + segment.
- **Frame**: a link-layer PDU = link header + datagram.

Each layer **encapsulates** the PDU from the layer above by adding its
own header.

---

## R25. Which layers does a router process? A switch? An end system?

- **Router**: Physical, Link, and **Network** layers (layers 1–3).
- **Switch** (link-layer switch): Physical and **Link** layers
  (layers 1–2).
- **End system (host)**: **all five** layers (Physical through
  Application).

---

# Section 1.6

## R26. What is self-replicating malware?

Malware that, once it infects a host, **automatically reproduces and
spreads itself** to other hosts without (or with minimal) user action.
The two classic forms are **viruses** (require some user action, e.g.,
opening an attachment, to spread) and **worms** (spread autonomously
over the network). Both can multiply exponentially across the Internet.

---

## R27. Describe how a botnet can be created and how it can be used in a DDoS attack.

- **Creating a botnet**: an attacker infects many vulnerable hosts with
  malware (via worms, malicious downloads, phishing, etc.). Each infected
  machine becomes a **bot** that secretly reports to and obeys the
  attacker's **command-and-control** server. Thousands/millions of bots
  form the botnet.
- **DDoS use**: the attacker commands **all bots simultaneously** to send
  traffic/requests to a **target server**. The flood of traffic from many
  distributed sources **overwhelms the target's bandwidth or resources**,
  making it unavailable to legitimate users.

---

## R28. Trudy can capture all packets between Alice and Bob and inject her own in either direction. List some malicious actions she can take.

From this **man-in-the-middle** position, Trudy can:

- **Sniffing / eavesdropping**: read the contents of all packets,
  stealing confidential data (passwords, messages).
- **Modification**: alter the contents of packets in transit before
  delivering them.
- **Deletion / interruption**: drop packets so messages never arrive
  (denial of service).
- **Spoofing / impersonation**: inject forged packets pretending to be
  Alice (to Bob) or Bob (to Alice).
- **Replay**: re-send previously captured packets to repeat an action.

---

## Further Reading

- *Computer Networking: A Top-Down Approach* — Kurose & Ross
  (Ch. 1: Computer Networks and the Internet)
- [What is the Internet Engineering Task Force (IETF)?](https://www.ietf.org/)
