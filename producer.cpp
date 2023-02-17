#include <iostream>
#include <string>
#include <vector>
#include <cppkafka/cppkafka.h>
using namespace std;
using namespace cppkafka;
// Define an Ethernet frame class
class EthernetFrame
{
public:
    std::string srcMac;
    std::string dstMac;
    uint16_t type;
    std::vector<char> payload;

    void Serialize(std::ostream &stream) const
    {
        stream.write(srcMac.data(), srcMac.size());
        stream.write(dstMac.data(), dstMac.size());
        stream.write(reinterpret_cast<const char *>(&type), sizeof(type));
        stream.write(payload.data(), payload.size());
    }

    void Deserialize(std::istream &stream)
    {
        std::getline(stream, srcMac, ':');
        std::getline(stream, srcMac, ':');
        std::getline(stream, srcMac, ':');
        std::getline(stream, srcMac, ':');
        std::getline(stream, srcMac, ':');
        std::getline(stream, srcMac, ':');
        std::getline(stream, dstMac, ':');
        std::getline(stream, dstMac, ':');
        std::getline(stream, dstMac, ':');
        std::getline(stream, dstMac, ':');
        std::getline(stream, dstMac, ':');
        stream.read(reinterpret_cast<char *>(&type), sizeof(type));
        payload.resize(stream.tellp());
        stream.read(payload.data(), payload.size());
    }
};

int main()
{
    Producer producer({{"metadata.broker.list", "localhost:9092"}});

    // Create a Kafka topic
    Topic topic(producer, "my-topic",
                {{"request.required.acks", "all"}});

    // Create an Ethernet frame object
    EthernetFrame frame;
    frame.srcMac = "aa:bb:cc:dd:ee:ff";
    frame.dstMac = "11:22:33:44:55:66";
    frame.type = 0x800;
    frame.payload = {'H', 'e', 'l', 'l', 'o', ', ', ' ', 'w ', ' o ', ' r ', ' l ', ' d ', ' !'};

    // Serialize the Ethernet frame into a Buffer
    std::stringstream stream;
    frame.Serialize(stream);
    Buffer payload(stream.str());

    // Send the Ethernet frame to the Kafka topic
    Message message = MessageBuilder("first_topic").partition(3).payload(payload);
    producer.produce(message);

    return 0;
}
