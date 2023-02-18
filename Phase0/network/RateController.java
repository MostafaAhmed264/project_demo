package Phase0.network;

import Phase0.GlobalVariable;

public class RateController
{
    public static void setRate(String interfaceName, String sendRate, String receiveRate) throws Exception {
        System.out.println("HELLOOOOOO");
        System.out.println("HELLOOOOOO");
        System.out.println("HELLOOOOOO"); System.out.println("HELLOOOOOO"); System.out.println("HELLOOOOOO"); System.out.println("HELLOOOOOO"); System.out.println("HELLOOOOOO");



        String command = "sudo wondershaper " + GlobalVariable.interfaceName + " " + receiveRate + " " + sendRate;
        System.out.println(command);
        SystemAnalyser system = new SystemAnalyser();
        system.runCommand(command); // Run script in shell
        // String output = system.outputStore; // Output from terminal (command)


    }

    // return interface to default state (Max rate)
    public static void setDefault(String interfaceName) throws Exception {
        String command = "sudo wondershaper clear " + GlobalVariable.interfaceName;
        SystemAnalyser system = new SystemAnalyser();
        system.runCommand(command); // Run script in shell
        //String output = system.outputStore; // Output from terminal (command)
    }

    public static void test() throws Exception {
        setRate("enp37s0", "10000", "10");
    }
}