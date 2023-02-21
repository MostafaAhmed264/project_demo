package org.example;

import org.pcap4j.core.*;
import org.pcap4j.packet.Packet;
import org.pcap4j.packet.namednumber.DataLinkType;

import java.net.Inet4Address;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

public class PacketSniffer {
    private PcapHandle handler;
    private PcapNetworkInterface nif ;
    private BpfProgram pr;
    private String filter;
    private int num_packets;

    public PacketSniffer(String s, int num_packets)
    {
        filter = s;
        this.num_packets = num_packets;
    }
    public PacketSniffer(String s)
    {
        libpcap_init();

        setFilter(s);

    }
    public  void libpcap_init()
    {
        try
        {
            //select using terminal
            //nif = new NifSelector().selectNetworkInterface();
            List<PcapNetworkInterface> allDevs = Pcaps.findAllDevs();
            nif = allDevs.get(0);
        }
        catch (Exception ex)
        {
            System.out.println("Problem in setting pcap network device");
        }
        int snapLen = 2048;
        PcapNetworkInterface.PromiscuousMode mode = PcapNetworkInterface.PromiscuousMode.NONPROMISCUOUS;
        int timeout = 100;
        try
        {
            handler = nif.openLive(snapLen, mode, timeout);
        }
        catch(Exception ex)
        {
            System.out.println("Problem in opening session");

        }
    }

    public  void setFilter(String expr)
    {
        try {
            pr = Pcaps.compileFilter(2048 ,new DataLinkType(1, "Ethernet"),
                    expr,BpfProgram.BpfCompileMode.NONOPTIMIZE, (Inet4Address) nif.getAddresses().get(0).getNetmask());
            handler.setFilter(pr);
        }
      catch (Exception e){
          System.out.println("COULDNT SET FILTER");
      }
    }
    public Packet readPacket()
    {
        Packet p = null;
        try {
             p = handler.getNextPacket();

            while (p == null) {
                p = handler.getNextPacket();
            }
        }
        catch (Exception e){
            System.out.println("ah");
        }

        return p;
    }
    void close_session()
    {
        handler.close();
    }
}
