#!/usr/bin/python                                                                            
                                                                                             
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel

class SingleSwitchTopo(Topo):
    "Single switch connected to n hosts."
    def build(self, n=2):
        s1 = self.addSwitch('s1')
        s2 = self.addSwitch('s2')
        s3 = self.addSwitch('s3')
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        h3 = self.addHost('h3')
        h4 = self.addHost('h4')
        self.addLink( s1, s2, bw=20, loss=0)
        self.addLink( s1, s3, bw=20, loss=0)
        self.addLink( s1, h1)
        self.addLink( s1, h4)
        self.addLink( s2, h2)
        self.addLink( s3, h3)
        
def perfTest():
    "Create network and run simple performance test"
    topo = SingleSwitchTopo()
    net = Mininet( topo=topo,
	           host=CPULimitedHost, link=TCLink )
    net.start()
    h1, h2, h3, h4= net.get( 'h1', 'h2', 'h3', 'h4')
    net.iperf( (h1, h2) )
    net.iperf( (h1, h3) )
    net.iperf( (h1, h4) )
    net.iperf( (h2, h3) )
    net.iperf( (h2, h4) )
    net.iperf( (h3, h4) )
    net.stop()

if __name__ == '__main__':
    # Tell mininet to print useful information
    setLogLevel('info')
    perfTest()