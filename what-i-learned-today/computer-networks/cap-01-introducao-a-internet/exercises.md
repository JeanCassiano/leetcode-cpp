# Computer Networks — Ch. 1 (Kurose & Ross): Review Questions

Solutions to the **Review Questions** from Chapter 1 of *Computer
Networking: A Top-Down Approach* (Kurose & Ross).

---

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

## Further Reading

- *Computer Networking: A Top-Down Approach* — Kurose & Ross
  (Ch. 1: Computer Networks and the Internet)
- [What is the Internet Engineering Task Force (IETF)?](https://www.ietf.org/)
