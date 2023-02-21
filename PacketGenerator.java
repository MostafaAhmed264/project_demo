package org.example;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Random;
import java.util.SortedMap;

import org.pcap4j.core.NotOpenException;
import org.pcap4j.core.PcapHandle;
import org.pcap4j.core.PcapNativeException;
import org.pcap4j.core.PcapNetworkInterface;
import org.pcap4j.core.Pcaps;
import org.pcap4j.packet.*;
import org.pcap4j.packet.namednumber.*;
import org.pcap4j.util.MacAddress;

import javax.crypto.Mac;

public class PacketGenerator {
    private static final String COUNT_KEY = PacketGenerator.class.getName() + ".count";
    private static final int COUNT = Integer.getInteger(COUNT_KEY, 50);

    private static final String READ_TIMEOUT_KEY = PacketGenerator.class.getName() + ".readTimeout";
    private static final int READ_TIMEOUT = Integer.getInteger(READ_TIMEOUT_KEY, 10); // [ms]

    private static final String SNAPLEN_KEY = PacketGenerator.class.getName() + ".snaplen";
    private static final int SNAPLEN = Integer.getInteger(SNAPLEN_KEY, 65536); // [bytes]
   private static PcapNetworkInterface nif;

    private static PcapHandle handle;

    private PacketGenerator()
    {


    }

    public static void initializeNIF()
    {
        try
        {
            nif = Pcaps.getDevByName(GlobalVariable.interfaceName);
            handle = nif.openLive(SNAPLEN, PcapNetworkInterface.PromiscuousMode.PROMISCUOUS, READ_TIMEOUT);

        }
        catch (Exception ex)
        {
            System.out.println("Error in initializing packet generator");
        }
    }

    public static Inet4Address buildIpV4Address(String ip) throws UnknownHostException {
        return (Inet4Address) Inet4Address.getByName(ip);
    }

    public static MacAddress buildMacAddress(String mac) {
        return MacAddress.getByName(mac, ":");
    }


    public static EthernetPacket.Builder buildEtherHeader(Packet.Builder builder) {
        MacAddress srcMac = buildMacAddress(MACAddr.srcMacAddr);
        MacAddress dstMac = buildMacAddress(MACAddr.dstMacAddr);

        EthernetPacket.Builder etherBuilder = new EthernetPacket.Builder();
        etherBuilder
                .srcAddr(srcMac)
                .dstAddr(dstMac)
                .payloadBuilder(builder)
                .paddingAtBuild(true);

        if (builder instanceof IpV4Packet.Builder)
            etherBuilder.type(EtherType.IPV4);
        else
            etherBuilder.type(EtherType.IPV6);

        return etherBuilder;
    }

    private static UnknownPacket.Builder payLoadbuilder(String  payload) {
        UnknownPacket.Builder unknownBuilder = new UnknownPacket.Builder();
        unknownBuilder.rawData(payload.getBytes());
        return unknownBuilder;
    }

    private static UdpPacket.Builder buildUdpHeader(Packet.Builder builder) {
        UdpPacket.Builder udpBuilder = new UdpPacket.Builder();
        udpBuilder
                .dstPort(UdpPort.getInstance((short) 12345))
                .srcPort(UdpPort.getInstance((short) 54321))
                .payloadBuilder(builder)
                .correctChecksumAtBuild(false)
                .correctLengthAtBuild(true);
        return udpBuilder;
    }

    private static IpV4Packet.Builder buildIpV4Header(Packet.Builder builder) throws UnknownHostException {
        Inet4Address srcIp = buildIpV4Address(IP.srcIpAddr);
        Inet4Address dstIp = buildIpV4Address(IP.dstIpAddr);

        IpV4Packet.Builder ipBuilder = new IpV4Packet.Builder();
        ipBuilder
                .version(IpVersion.IPV4)
                .tos((IpV4Packet.IpV4Tos) () -> (byte) 0)
                .identification((short) new Random().nextInt())
                .ttl((byte) 100)
                .srcAddr(srcIp)
                .dstAddr(dstIp)
                .payloadBuilder(builder)
                .correctChecksumAtBuild(true)
                .correctLengthAtBuild(true);

        if (builder instanceof UdpPacket.Builder)
            ipBuilder.protocol(IpNumber.UDP);
        else
            ipBuilder.protocol(IpNumber.TCP);

        return ipBuilder;
    }


    public static EthernetPacket buildPacket(String  payload) {
        EthernetPacket packet = null;
        try {
           packet = buildEtherHeader(buildIpV4Header(buildUdpHeader(payLoadbuilder(payload)))).build();
        }
        catch (Exception e)
        {

            System.out.println("can't build ethernet packet");

        }
        return packet;
    }


    public static void sendPacket(Packet packet, int num_packets) {

        try
        {
            for (int i = 0; i < num_packets; i++)
            {
                handle.sendPacket(packet);
            }
        }
        catch (Exception e)
        {
            System.out.println("Error in sending");
            e.printStackTrace();
        }

    }


    public static void sendPacket(Packet packet)
    {
        try
        {
            handle.sendPacket(packet);
        }
        catch (Exception e)
        {
            System.out.println("Error in sending");
            e.printStackTrace();
        }
    }
    void close_session()
    {
        handle.close();
    }


    public static void main(String[] args) throws NotOpenException, PcapNativeException {
        PacketSniffer s1 = new PacketSniffer("port 12345");
        Runnable myThread = () ->
        {
            while (true){
                Packet p =s1.readPacket();
                System.out.println(p);
            }


        };
        Thread t = new Thread(myThread);
        t.start();

        //sendPacket("1", 100000);
        try {
            t.join();
        }
        catch (Exception E){

            System.out.println("sdsadasd");

        }



    }

}