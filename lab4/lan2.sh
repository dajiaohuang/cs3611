sudo ifconfig s2 10.0.0.4/8 up
sudo ovs-vsctl add-br br1
sudo ovs-vsctl add-port br1 ens33
sudo ifconfig br1 192.168.56.102/24 up
sudo route add default gw 192.168.56.201
sudo ovs-vsctl add-port s2 vxlan0 -- set interface vxlan0 type=vxlan options:remote_ip=192.168.56.101