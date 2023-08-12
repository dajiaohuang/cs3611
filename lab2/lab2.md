1. 

![image-20230413171153147](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230413171153147.png)

2.

![image-20230413172141728](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230413172141728.png)

3. 

![image-20230413231303524](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230413231303524.png)

If no extra flow is applied, pingall will fail as the ping signal go into the loop. 

From net command we can know the ports' id. Accorrding to the id, we can write such an sh, and add these flow to the switchers, so that every time the switchers are reached, we search for hosts first and the switchers.

![image-20230413232517673](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230413232517673.png)

The sh specifies in what order we search the ports when the signal comes from a specific in-port, which is basically host first, switchers next, never go back. 

 ![image-20230413231424420](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20230413231424420.png)

With this scheme, the ping-all succeeds.