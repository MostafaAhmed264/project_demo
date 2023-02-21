package org.example;

public class PacketLossSendThread implements Runnable
{
    PacketLossSend p1  = new PacketLossSend();

    @Override
    public void run()
    {
        p1.ping();

    }
}
