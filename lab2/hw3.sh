#!/bin/sh
sudo ovs-ofctl add-flow s2 "in_port=s2-eth1,actions=output:s2-eth3,s2-eth2"
sudo ovs-ofctl add-flow s3 "in_port=s3-eth2,actions=output:s3-eth3,s3-eth1"
sudo ovs-ofctl add-flow s3 "in_port=s3-eth1,actions=output:s3-eth3,s3-eth2"
sudo ovs-ofctl add-flow s2 "in_port=s2-eth2,actions=output:s2-eth3,s2-eth1"
sudo ovs-ofctl add-flow s1 "in_port=s1-eth1,actions=output:s1-eth3,s1-eth4,s1-eth2"
sudo ovs-ofctl add-flow s1 "in_port=s1-eth2,actions=output:s1-eth3,s1-eth4,s1-eth1"
