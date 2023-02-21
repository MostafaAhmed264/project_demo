package org.example;

import org.pcap4j.packet.EthernetPacket;

import java.net.UnknownHostException;

public class PacketLossSend extends  Ping
{
    public static int windowSize = 1000;
    @Override
    public void ping() {
        //set udp or tcp ports by the port that will be assigned for packet loss pinging
        String payload = "1";
        int payloadIntValue;
        EthernetPacket packet;
        PacketGenerator.initializeNIF();
        for (int i = 0 ; i <windowSize ;i++)
        {
            packet = PacketGenerator.buildPacket(payload);
            PacketGenerator.sendPacket(packet);
            payloadIntValue = Integer.parseInt(payload);
            payloadIntValue++;
            payload = payloadIntValue+"";
        }
    }

    public static void main(String[] args)
    {
        PacketLossSend p1 = new PacketLossSend();
        p1.ping();
    }
}
