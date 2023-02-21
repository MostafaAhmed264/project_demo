package org.example;

import org.pcap4j.packet.Packet;
import org.pcap4j.packet.UdpPacket;
import org.pcap4j.packet.namednumber.UdpPort;

public class PacketLossReciever implements EchoPacket{
    PacketSniffer packetSniffer;
    PacketLossReciever(PacketSniffer sniffer)
    {
        this.packetSniffer = sniffer;

    }
    public void echoPacket()
    {
        Packet packet;
        try
        {
            packet = packetSniffer.readPacket();
            Packet.Builder builder = packet.getBuilder();
            builder.get(UdpPacket.Builder.class).dstPort(UdpPort.getInstance((short) 777));
            packet = builder.build();
            System.out.println(packet);

            PacketGenerator.sendPacket(packet);
        }
        catch(Exception e)
        {
            System.out.println("couldn't read packets");
            e.printStackTrace();
        }
    }
}
