sudo ifconfig s1 10.0.0.3/8 up
sudo ovs-vsctl add-br br1
sudo ovs-vsctl add-port br1 ens33
sudo ifconfig br1 192.168.56.101/24 up
sudo route add default gw 192.168.56.201
sudo ovs-vsctl add-port s1 vxlan0 -- set interface vxlan0 type=vxlan options:remote_ip=192.168.56.102