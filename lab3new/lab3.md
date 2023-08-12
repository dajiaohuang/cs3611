1. Topology

   ![image-20230511000713345](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230511000713345.png)

   ![image-20230511000749532](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230511000749532.png)

2. Chat room with TCP

   The center h5 is created in center.cpp, and h1,2,3,4 are created in user.cpp.  Because h1,2,3,4 actually only interact with h5, we use lpthread so that we don't need to create a new socket every time. To compile them, following commands are need instead. 

   ![image-20230511001625546](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230511001625546.png)

   ![image-20230511001710240](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230511001710240.png)

3. Chat room with UDP

   The message is broadcasted, the broadcast address is "10.255.255.255" 
   
   My udpclient.cpp file is based on the examples given on the website. In the for loop, there is a if-statement: if strcmp(rv_addr, local_addr). If the sender’s IP is the same as mine, it means I’m exactly the sender, then I will not display it. Otherwise, I print the message. 

.![捕获](F:\计网\lab3\捕获.PNG)