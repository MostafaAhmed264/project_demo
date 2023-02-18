package Phase0;

import Phase0.commands.MachineCommand;
import Phase0.kafka.GenericConsumer;
import Phase0.network.PacketGenerator;
import Phase0.network.RateController;
import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.pcap4j.core.NotOpenException;
import org.pcap4j.core.PcapNativeException;

import java.net.UnknownHostException;

public class SingleMachine {
    static int   machineId = 0;
    public static void main(String[] args) {

        Thread t1 = new Thread(() -> ContinuousConsume());
        t1.start();




    }
    static void ContinuousConsume()
    {
        GenericConsumer consumer = new GenericConsumer("192.168.1.3:9093","0");
        consumer.selectTopic("CMD_FromHPC_Master");
        while(true)
        {
            ConsumerRecords<String, String> records =consumer.consume(1000);

            for (ConsumerRecord<String, String> record : records) {
                String json = record.value();
                MachineCommand command = JSONConverter.fromJSON(json, MachineCommand.class);
                if(command.getMachineID() == machineId)
                {
                    //stub for sending packets
                    Thread t1 = new Thread(() -> {
                        try {
                            handleCommand(command);
                        } catch (Exception e) {
                            throw new RuntimeException(e);
                        }
                    });
                    t1.start();
                }
            }

        }
    }
    static void  handleCommand(MachineCommand command) throws Exception {

        if (command.getMode().equals("Sender"))
        {
            /*
                set sending rate
             */
            System.out.println(command.getRates());
            RateController.setRate("enp37s0", Integer.toString((int)command.getRates()),"100" );


            /*
                open a thread for sending with the command parameters
                should make the parameters more configurable later
             */
            Thread t1 = new Thread(() -> {
                try {
                    PacketGenerator.send("192.168.1.2", "3C:2C:30:9B:3B:90", command.getPackets());
                } catch (PcapNativeException e) {
                    throw new RuntimeException(e);
                } catch (NotOpenException e) {
                    throw new RuntimeException(e);
                } catch (UnknownHostException e) {
                    throw new RuntimeException(e);
                }
            });
            t1.start();
        }
    }
}

