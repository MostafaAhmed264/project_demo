package Phase0.network;

import java.net.Inet4Address;
import java.net.UnknownHostException;
import java.util.Random;

import Phase0.miscellaneous.GlobalVariable;
import org.pcap4j.core.NotOpenException;
import org.pcap4j.core.PcapHandle;
import org.pcap4j.core.PcapNativeException;
import org.pcap4j.core.PcapNetworkInterface;
import org.pcap4j.core.Pcaps;
import org.pcap4j.packet.*;
import org.pcap4j.packet.namednumber.*;
import org.pcap4j.util.MacAddress;

public class PacketGenerator {
    private static final String COUNT_KEY = PacketGenerator.class.getName() + ".count";
    private static final int COUNT = Integer.getInteger(COUNT_KEY, 50);

    private static final String READ_TIMEOUT_KEY = PacketGenerator.class.getName() + ".readTimeout";
    private static final int READ_TIMEOUT = Integer.getInteger(READ_TIMEOUT_KEY, 10); // [ms]

    private static final String SNAPLEN_KEY = PacketGenerator.class.getName() + ".snaplen";
    private static final int SNAPLEN = Integer.getInteger(SNAPLEN_KEY, 65536); // [bytes]

    private PacketGenerator() {
    }

    public static void send(String strDstIp, String strDstMac, long num_packets) throws PcapNativeException, NotOpenException, UnknownHostException {
        String strSrcIp = "192.168.1.1";
        String strSrcMac = "00:00:00:00:00:01";


        MacAddress srcMac = MacAddress.getByName(strSrcMac, ":");
        MacAddress dstMac = MacAddress.getByName(strDstMac, ":");
        System.out.println(srcMac);
        Inet4Address srcIp = (Inet4Address) Inet4Address.getByName(strSrcIp);
        Inet4Address dstIp = (Inet4Address) Inet4Address.getByName(strDstIp);
        System.out.println(srcIp);
        EthernetPacket.Builder etherBuilder = new EthernetPacket.Builder();

// Set up UDP packet builder

        UnknownPacket.Builder unknownb = new UnknownPacket.Builder();
        unknownb.rawData(new byte[1000]);
        UdpPacket.Builder udpBuilder = new UdpPacket.Builder();
        udpBuilder
                .dstPort(UdpPort.getInstance((short) 12345))
                .srcPort(UdpPort.getInstance((short) 54321))
                .payloadBuilder(unknownb)
                .correctChecksumAtBuild(false)
                .correctLengthAtBuild(true);

// Set up IP packet builder
        IpV4Packet.Builder ipBuilder = new IpV4Packet.Builder();
        ipBuilder
                .version(IpVersion.IPV4)
                .tos((IpV4Packet.IpV4Tos) () -> (byte)0)
                .identification((short) new Random().nextInt())
                .ttl((byte) 100)
                .protocol(IpNumber.UDP)
                .srcAddr(srcIp)
                .dstAddr(dstIp)
                .payloadBuilder(udpBuilder)
                .correctChecksumAtBuild(true)
                .correctLengthAtBuild(true);

// Set up Ethernet packet builder
        etherBuilder
                .srcAddr(srcMac)
                .dstAddr(dstMac)
                .type(EtherType.IPV4)
                .payloadBuilder(ipBuilder)
                .paddingAtBuild(true);

// Build packet
        EthernetPacket etherPacket = etherBuilder.build();

// Send packets
        PcapNetworkInterface nif = Pcaps.getDevByName(GlobalVariable.interfaceName);
        PcapHandle handle = nif.openLive(SNAPLEN, PcapNetworkInterface.PromiscuousMode.PROMISCUOUS, READ_TIMEOUT);
        /*
            open thread for observer and produce in kafka
         */
        Thread t = new Thread(() -> Observer.observe());
        t.start();
        for (int i = 0; i < num_packets; i++) {
            handle.sendPacket(etherPacket);
        }
        handle.close();
        t.interrupt();
    }
}