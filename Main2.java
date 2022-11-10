package org.example;

public class Main2 {
    public static void main(String[] args) throws InterruptedException {

        Capturer c1 = new Capturer("greater 1400 and less 1400 and port 777",10000);
        Thread object1 = new Thread(c1);
        Capturer c2 = new Capturer("greater 1450 and less 1450 and port 777",10000);
        Thread object2 = new Thread(c2);
        object1.start();
        object2.start();
        object1.join();
        object2.join();

        System.out.println("-------------------------TIME CALC--------------------------------");
        double [] time1_c1 = c1.get_time(c1.firstRecievedPacket.toString());
        double [] time1_c2 = c2.get_time(c2.firstRecievedPacket.toString());
        double secs1 = time1_c1[0] * 60  + time1_c1[1];
        double secs2 = time1_c2[0] * 60  + time1_c2[1];
        if (secs1 > secs2)
        {
           secs1 = secs2;
        }

        //double [] time1 = c1.get_time(c1.firstRecievedPacket.toString());
        double [] time2 = c1.get_time(Capturer.lastRecievedPacket.toString());
        //double secs1 = time1[0] * 60  + time1[1];
        secs2 = time2[0] * 60  + time2[1];
        //secs2 = time2[0] * 60  + time2[1];

        System.out.println("Diff in seconds : " + (secs2 - secs1));
        System.out.println("Rate :" +  ((20000*1425) / ((secs2 - secs1) * 1024 * 1024)));
    }
}