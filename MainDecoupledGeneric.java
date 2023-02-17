import org.apache.kafka.common.serialization.ByteArraySerializer;
import org.apache.kafka.common.serialization.StringSerializer;

/**
 * partition 0 2756896   2763539  6643
 *
 * partition 1 2752132   2758777  6645
 *
 * partition 2 2744282   2750994  6712
 */
public class MainDecoupledGeneric {
    public static void main(String[] args) throws InterruptedException {


//        GlobalVariable.queue = new LinkedList<byte[]>();


        int j =0;
        while (j < 80000)
        {
            CapturerDecoupled c1 = new CapturerDecoupled("greater 1400 and less 1400 and port 777",10000);
            Thread object1 = new Thread(c1);
            CapturerDecoupled c2 = new CapturerDecoupled("greater 1450 and less 1450 and port 777",10000);
            Thread object2 = new Thread(c2);
            producerGeneric<String, byte[]> producer=new producerGeneric<>(c1.queue, StringSerializer.class.getName());
            Thread producerTh = new Thread(producer);
            producerGeneric<String, byte[]> producer1=new producerGeneric<>(c2.queue,StringSerializer.class.getName());
            Thread producerTh1 = new Thread(producer1);
            object1.start();
            object2.start();
            producerTh.start();
            producerTh1.start();
            object1.join();
            object2.join();

            j++;
        }


//        System.out.println("-------------------------TIME CALC--------------------------------");
//        double [] time1_c1 = c1.get_time(c1.firstRecievedPacket.toString());
//        double [] time1_c2 = c2.get_time(c2.firstRecievedPacket.toString());
//        double secs1 = time1_c1[0] * 60  + time1_c1[1];
//        double secs2 = time1_c2[0] * 60  + time1_c2[1];
//        if (secs1 > secs2)
//        {
//           secs1 = secs2;
//        }
//
//        //double [] time1 = c1.get_time(c1.firstRecievedPacket.toString());
//
//        double [] time2 = c1.get_time(CapturerDecoupled.lastRecievedPacket.toString());
//        //double secs1 = time1[0] * 60  + time1[1];
//        secs2 = time2[0] * 60  + time2[1];
//        //secs2 = time2[0] * 60  + time2[1];
//
//        System.out.println("Diff in seconds : " + (secs2 - secs1));
//        System.out.println("Rate :" +  ((20000*1425) / ((secs2 - secs1) * 1024 * 1024)));
//        //preventing the program from closing
//
//        System.out.println("hello world");
//        producerTh.join();
//        producer.closeProducer();
    }


}