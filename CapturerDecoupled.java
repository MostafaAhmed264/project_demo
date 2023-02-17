import org.pcap4j.core.*;
import org.pcap4j.packet.Packet;
import org.pcap4j.packet.namednumber.DataLinkType;

import java.net.Inet4Address;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

public class CapturerDecoupled implements Runnable
{
    public LinkedBlockingQueue<byte[]> queue;
    public  Packet firstRecievedPacket;
    public  static Packet lastRecievedPacket;
    private  PcapHandle handler;
    private  PcapNetworkInterface nif ;
    private BpfProgram pr;

    private String filter;

    private int num_packets;
//    private producerFunc producer;

    public CapturerDecoupled(String s, int num_packets)
    {
        filter = s;
        this.num_packets = num_packets;
        /**
         * for every capturer thread there will be a queue
         */
        queue = new LinkedBlockingQueue<byte[]>(20000);;
    }


    public void run()
    {
        byte[] bytes;
//        System.out.println("Hello world!");
        this.libpcap_init();
        try
        {
            this.setFilter(filter);
        }
        catch (Exception ex)
        {
            System.out.println("Error in setting filter");
        }
        try
        {
            int count =0;
            while (count < num_packets)
            {
                Packet packet = handler.getNextPacket();
                if (packet == null)
                {
                    continue;
                }
//                System.out.println("Packet number:" + (count+1));
                // if we want to get packet as bytes simply call packet.getRawData
                 bytes = packet.getRawData();
//                 producer.produce(bytes);
                queue.add(bytes);

//                System.out.println(packet);
                if (count == 0)
                {
                    firstRecievedPacket = packet;
                }
                else if (count == num_packets - 1)
                {
                    lastRecievedPacket = packet;
                }
                count++;
            }
        }
        catch (Exception ex)
        {
            System.out.println("Cannot read packets");
        }

        this.close_session();
    }
    public  void libpcap_init()
    {
        try {
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
    public  void setFilter(String expr) throws PcapNativeException, NotOpenException
    {
        pr = Pcaps.compileFilter(2048 ,new DataLinkType(1, "Ethernet"),expr,BpfProgram.BpfCompileMode.NONOPTIMIZE, (Inet4Address) nif.getAddresses().get(0).getNetmask());
        handler.setFilter(pr);
    }
    public  void read_packets(int packet_count) throws NotOpenException {
        int count =0;
        while (count < packet_count)
        {
            Packet packet = handler.getNextPacket();
            if (packet == null)
            {
                continue;
            }
//            System.out.println("Packet number:" + (count+1));
            // if we want to get packet as bytes simply call packet.getRawData
//            System.out.println(packet);
            if (count == 0)
            {
                firstRecievedPacket = packet;
            }
            else if (count == packet_count - 1)
            {
                lastRecievedPacket = packet;
            }
            count++;
        }

    }
     void close_session()
    {
        handler.close();
    }

     double[] get_time(String packet_str)
    {
        //Time array first mins the sec
        double [] time = new double[2];
        double time_sec;
        double time_min;

        //parsing packet data to get time
        int i = 26;
        StringBuilder min = new StringBuilder("");
        StringBuilder sec = new StringBuilder("");
        if (packet_str.charAt(i++) == ':')
        {
            while (packet_str.charAt(i) != ':'){
                min.append(packet_str.charAt(i));
                i++;
            }
        }
        if (packet_str.charAt(i++) == ':')
        {
            while (packet_str.charAt(i) != '+'){
                sec.append(packet_str.charAt(i));
                i++;
            }
        }
        //Changing parsed Strings to values
        time_min = Double.parseDouble(min.toString());
        time_sec = Double.parseDouble(sec.toString());
        time [0] = time_min;
        time [1] = time_sec;
        return time;
    }

}