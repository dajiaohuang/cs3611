1. 1. To add a new default route for vm1,vm2 respectively, we can add following code to step1:

      On vm1: sudo route add default gw 192.168.56.201

      On vm2: sudo route add default gw 192.168.56.201

   2. To Build the VXLAN tunnel and set the remote IP address as 192.168.56.102, add this to vm1 in step2:

      sudo ovs-vsctl add-port s1 vxlan0 -- set interface vxlan0 type=vxlan options:remote_ip=192.168.56.102

      To Build the VXLAN tunnel and set the remote IP address as 192.168.56.101, add this to vm2 in step2:

      sudo ovs-vsctl add-port s2 vxlan0 -- set interface vxlan0 type=vxlan options:remote_ip=192.168.56.101

2.  First check the config

   use:   sudo ifconfig -a

   ![image-20230529000520983](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529000520983.png)

   There's no enp0s8, so I modify "enp0s8" in the given code into "ens33", so that there won't be an error. And put those commands in lan1.sh and lan2.sh

   ![image-20230529000730658](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529000730658.png)

   Run the sh files.

   ![image-20230529000811266](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529000811266.png)

   Then use xterm and ping 10.0.0.1 from 10.0.0.2.

   ![image-20230529000342373](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529000342373.png)

   Also ping reversely.

   ![image-20230529001009651](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529001009651.png)

   Wireshark when ping 10.0.0.2 from 10.0.0.1:

   ens33:

   ![image-20230529002322591](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529002322591.png)

   s1-eth1:

   ![image-20230529002617897](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529002617897.png)

   s2-eth1:

   ![image-20230529002441373](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529002441373.png)

   We can see that ICMP,AMP are used.

3.  sudo iperf3 -s 10.0.0.4 on s1

   ![image-20230529001557083](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529001557083.png)

   sudo iperf3 -c 10.0.0.3 on s2

   ![image-20230529001535343](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529001535343.png)

   Bandwidth is too small and there's no packet received. 

   This because of the MTU.

   From this figure we can get MTU of br1.

   ![image-20230529000520983](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529000520983.png)

   The MTU of br1 is 1500.

   Since ping is an application layer command, we know that a datagram length is consist of 20 bytes datagram header, 20 bytes TCP segment header and application message. And we need 50 bytes for VXLAN in this lab. So the MSS of application message is: 1500*−*20*−*20*−*50 = 1410.

   And local mtu is 65536, which is much bigger. So we waste much time packing and unpacking and in congestion.

4.   Designating the MTU size of iperf3:

   ![a478c232fe35cc9f68a600e3c33c193](C:\Users\Administrator\AppData\Local\Temp\WeChat Files\a478c232fe35cc9f68a600e3c33c193.png)

    ![image-20230529010025056](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529010025056.png)

   Bandwidth is improved. Because making the MTU of iperf3 smaller than that of br1 and ens33 (1500) avoids congestion, packing and unpacking.

   Designating the MTU of the two ens33 interfaces:

   ![image-20230529010858339](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529010858339.png)

   ![image-20230529011301635](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529011301635.png)

   ![image-20230529010936050](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230529010936050.png)

   Not improved. Because we can never modify this MTU to make it bigger than the local MTU to avoid packing and unpacking. Also MTU of bridge is not changed, so actually there's no real difference.

   

