**problem1** 

SMS (Short Message Service) is realized through the Mobile Application Part (MAP) of the SS7 protocol. It allows the sending and receiving of text messages between mobile phones over cellular networks.

iMessage is based on a proprietary, binary protocol APNs (Apple Push Notification Service). iMessage supports texts, photos, audios or videos that we send to iOS devices and Macs over cellular data network or WiFi. 

WhatsApp uses the XMPP protocol (Extensible Messaging and Presence Protocol). WhatsApp Messenger is an instant messenger service that supports many mobile platforms. 

iMessage and WhatsApp are different than SMS because they use data plan to send messages and they work on TCP/IP networks. iMessage and WhatsApp support sending different things, while the original SMS can only send text message. iMessage and WhatsApp can work via WiFi, but SMS cannot.

**problem2**

Application layer protocols: DNS and HTTP

Transport layer protocols: UDP for DNS; TCP for HTTP

**problem3**

1. The server able to successfully find the document. The reply was provided on Tuesday, 07 Mar 2008 12:40:46GMT.

2. The document index.html was last modified on Saturday 10 Dec 2005 18:28:47 GMT.

3.  There are 3848 bytes in the document being returned.

4.  <!doc

    The server agreed to a persistent connection, as indicated by the Connection: Keep-Alive.

**problem4**

The total amount of time to get the IP address is $$\sum_{i=1}^{n}RTT_i$$

$RTT_0$ elapses respectively when TCP is set and the object is transmitted.

So, total time amount is $$2RTT_0+ \sum_{i=1}^{n}RTT_i$$

**problem5**

1. $$16 RTT_0 +\sum_{i=1}^{n}RTT_i$$

2. $$6 RTT_0 +\sum_{i=1}^{n}RTT_i$$

3. $$3 RTT_0 +\sum_{i=1}^{n}RTT_i$$ with pipelining

   $$9 RTT_0 +\sum_{i=1}^{n}RTT_i$$without pipelining

**problem6**

1. 750000bits/15Mbps = 0.05s

   average access delay = 0.05/(1-0.05x18)=0.5

   Average response time= average access delay + average Internet delay=0.5+2=2.5s

2. Response time when miss =2.5s

   Total response time = 0.6x0+0.4x2.5 = 1s

**problem7**

$$D_{cs}=max(NF/u_s,F/d)$$

$$D_{p2p}=max(F/u_s,F/d,NF/(u_s+Nu))$$

Client-Server

|         | 10   | 100   | 1000   |
| ------- | ---- | ----- | ------ |
| 300Kbps | 7500 | 50000 | 500000 |
| 700Kbps | 7500 | 50000 | 500000 |
| 2Mbps   | 7500 | 50000 | 500000 |

P2P

|         | 10   | 100   | 1000  |
| ------- | ---- | ----- | ----- |
| 300Kbps | 7500 | 25000 | 45455 |
| 700Kbps | 7500 | 15000 | 20548 |
| 2Mbps   | 7500 | 7500  | 7500  |

