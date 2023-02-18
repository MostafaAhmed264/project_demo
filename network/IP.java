package Phase0.network;

/**
 * this class will hold all the ip of the machines that will be used
 * later this will be taken from a configuration file
 */
public class IP {
    public static String ip1 ="localhost";

    // this ip was used to consume from the broker that contains cmdFromHpcMaster
    public static String singleMachine1Ip = "192.168.1.3";
    //this ip is used by the PacketGenerator in the SingleMachine class
    public static String receiverOfPackets ="192.168.1.2";

}
