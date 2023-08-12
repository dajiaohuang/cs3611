

1. 1. | Destination Prefifix | Link Interface |
      | -------------------- | -------------- |
      | 11100000 00          | 0              |
      | 11100000 01000000    | 1              |
      | 1110000              | 2              |
      | 11100001 1           | 3              |
      | otherwise            | 3              |

   2. | Destination Prefifix | Link Interface |
      | -------------------- | -------------- |
      | 224.0/10             | 0              |
      | 224.64/16            | 1              |
      | 224/7                | 2              |
      | 224.128/9            | 2              |
      | otherwise            | 3              |

   3. | Destination Prefifix                | Link Interface         |
      | ----------------------------------- | ---------------------- |
      | 11000000 00010001 01010001 01010101 | 0 (matching 1st entry) |
      | 11100000 01000000 11000011 00111100 | 1 (matching 2st entry) |
      | 11100001 10000000 00010001 01110111 | 3 (matching 4st entry) |
      | 11100000 01000000 00001000 00000001 | 1 (matching 2st entry) |

2. 1. Subnet A: 214.20.255/24 (256 addresses)

      Subnet B: 214.20.254.0/25 - 214.20.254.0/29 (128-8 = 120 addresses)

      Subnet C: 214.20.254.128/25 (128 addresses)

      Subnet D: 214.20.254.0/31 (2 addresses)

      Subnet E: 214.20.254.2/31 (2 addresses)

      Subnet F: 214.20.254.4/30 (4 addresses)

   2. 1. R1

         | Longest Prefix Match | Outgoing Interface |
         | -------------------- | ------------------ |
         | 214.20.255/24        | A                  |
         | 214.20.254.0/31      | D                  |
         | 214.20.254.4/30      | F                  |

      2. R2

         | Longest Prefix Match | Outgoing Interface |
         | -------------------- | ------------------ |
         | 214.20.254.128/25    | C                  |
         | 214.20.254.2/31      | E                  |
         | 214.20.254.4/30      | F                  |

      3. R3

         | Longest Prefix Match | Outgoing Interface |
         | -------------------- | ------------------ |
         | 214.20.254.0/25      | B                  |
         | 214.20.254.0/31      | D                  |
         | 214.20.254.2/31      | E                  |

3. |      | u    | v    | x    | y    | z    |
   | ---- | ---- | ---- | ---- | ---- | ---- |
   | v    |      |      |      |      |      |
   | x    |      |      |      |      |      |
   | z    |      | 4    | 2    |      | 0    |

   |      | u    | v    | x    | y    | z    |
   | ---- | ---- | ---- | ---- | ---- | ---- |
   | v    | 1    | 0    | 3    |      | 4    |
   | x    |      | 3    | 0    | 3    | 2    |
   | z    | 5    | 4    | 2    | 5    | 0    |

   |      | u    | v    | x    | y    | z    |
   | ---- | ---- | ---- | ---- | ---- | ---- |
   | v    | 1    | 0    | 3    | 3    | 4    |
   | x    | 4    | 3    | 0    | 3    | 2    |
   | z    | 5    | 4    | 2    | 5    | 0    |

4. LSR and DVR are two main routing algorithms. Coparison:

   1. message complexity: n nodes, e links

      LSR:  O(nE) msgs sent

      DVR: O(n) msgs sent

   2. computation complexity:

      LSR: Dijkstra $O(n^2)$

      DVR: Bellman Ford $O(n)$

   3. speed of convergence:

      LSR: 1 iteration, may have oscillations

      DVR: n iterations, may have count-to-infinity problem

   4. Robustness:

      LSR: robust. Node route calculations are somewhat separated

      DVR: not robust, incorrect node calculation can be diffused through the entire network.

   According the above analysis, LSR variants are suitable for small networks, and DVR variants are suitable for relatively large networks.

   Scenarios and example for avoiding count-to-infinity problem:

   RIP: DVR based. The distance metric is # of hops, limits networks to 15 hops (16 = *∞*to avoid count-to-infinity)

   OSPF: LSR based. Hierarchical OSPF for large networks.

   BGP: DVR based. DVR with explicit AS path avoid count-to-infinity

5. 1. Policy: 
      1. Inter-AS: admin wants control over how its traffic routed, and who routes through its net. (untrusted)
      2. Intra-AS: single admin, so no policy decisions needed (trusted)
   2. Performance:
      1. Intra-AS: can focus on performance
      2. Inter-AS: policy dominates over performance

6.  Methods:

   1. Use prefix instead of whole IP address.
   2. Use CIDR to converge multiple continuous IP prefix into one.
   3. Using hierarchical routing to reduce destination prefix.

7. To provide more IP addresses, simplify the IP header, speed up the routing processing, and support more features, including QoS, IP security.

8. | network | prefix       | mask            |
   | ------- | ------------ | --------------- |
   | LAN0    | 206.0.64.0   | 225.225.225.225 |
   | LAN1    | 206.0.64.0   | 225.225.225.128 |
   | LAN2    | 206.0.64.128 | 225.225.225.128 |
   | LAN3    | 206.0.65.0   | 225.225.225.128 |
   | LAN4    | 206.0.65.128 | 225.225.225.128 |
   | LAN5    | 206.0.66.0   | 225.225.225.192 |
   | LAN6    | 206.0.66.64  | 225.225.225.192 |
   | LAN7    | 206.0.66.128 | 225.225.225.192 |
   | LAN8    | 206.0.66.192 | 225.225.225.192 |
   | LAN9    | 206.0.67.0   | 225.225.225.192 |
   | LAN10   | 206.0.67.64  | 225.225.225.192 |
   | LAN11   | 206.0.67.128 | 225.225.225.192 |
   | LAN12   | 206.0.67.192 | 225.225.225.192 |

   