1. 1 1 1 0 1

   0 1 1 0 0

   1 0 0 1 0

   1 1 0 1 1

   1 1 0 0 0

2. If we divide 10011 into 1010101010 0000, we get 1011011100, with a remainder of R=0100. 

3. 1. Divide 10011 into 1010100000 0000, we get 1011010111, with a remainder of R=1001.
   2. Divide 10011 into 1001010101 0000, we get 1000110000, with a remainder of R=0000.
   3. Divide 10011 into 0101101010 0000, we get 0101010101, with a remainder of R=1111.

4.  IP and MAC

   ![image-20230529230047224](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529230047224.png)

   3. 1. Forwarding table in E determines that the datagram should be routed to interface 192.168.3.2
      2.  The adapter in E creates and Ethernet packet with Ethernet destination address 88-88-88-88-88-88
      3. Router receives the packet and extracts the datagram. The forwarding table in thisrouter indicates that the datagram is to be routed to 198.162.2.2
      4. Router then sends the Ethernet packet with the destination address of 55-55-55-55-55-55 and source address of 00-00-00-00-00-00 via its interface with IP address of 198.162.2.4
      5. Router then sends the Ethernet packet with the destination address of 22-22-22-22-22-22 and source address of 33-33-33-33-33-33 via its interface with 192.168.1.3
   4. ARP in E must now determine the MAC address of 198.162.3.2. Host E sends out an ARP query packet within a broadcast Ethernet frame. Router receives the query packet and sends to Host E an ARP response packet. This ARP response packet is carried by an Ethernet frame with Ethernet destination address 77-77-77-77-77-77.

5. A's transmision begin at t=0, and ends at t= 512+64=576. In the worst case, B's transmission begin at t=299, before it detects A's transmision and before first bit of A's transmision is completed so that the destination is taken by A. So at t= 299+300=599, the first bit of B's signal reaches A. 512+64=576<599. So A's transmission finishes before the collision is detected and  A incorrectly thinks that its frame was successfully transmitted without a collision
6. 1.  When B sends a frame to E, the switch learns interface corresponding to MAC of B. Then packets are forwarded to all 6 nodes because the switch table is empty.
   2. When E replies with a frame to B, the switch learns interface corresponding to MAC of E. Then packets are forwarded to B because B is already learnt.
   3. When  A sends a frame to B, the switch learns interface corresponding to MAC of A. Then packets are forwarded to B because B is already learnt.
   4. When B replies, nothing is learnt because B is already learnt. Then packets are forwarded to A because A is already learnt.