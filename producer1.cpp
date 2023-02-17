#include "kafka/KafkaProducer.h"
#include <iostream>
#include <string>
using namespace kafka;
using namespace kafka::clients;
using namespace kafka::clients::producer;
using namespace kafka;
using namespace kafka::clients;
using namespace kafka::clients::producer;

int main()
{
    // Set the broker list and topic
    std::string brokers = "localhost:9092";
    std::string topic = "test";

    // Create configuration object
    const Properties props({
        {"bootstrap.servers", {"localhost"}},
        {"enable.idempotence", {"true"}},
    });

    // Create a producer instance
    KafkaProducer producer(props);

    // Read messages from stdin and produce to the broker
    std::cout << "% Type message value and hit enter to produce message. (empty line to quit)" << std::endl;

    for (auto line = std::make_shared<std::string>();
         std::getline(std::cin, *line);
         line = std::make_shared<std::string>())
    {
        // The ProducerRecord doesn't own `line`, it is just a thin wrapper
        auto record = ProducerRecord(topic,
                                     NullKey,
                                     Value(line->c_str(), line->size()));

        // Send the message
        producer.send(record,
                      // The delivery report handler
                      // Note: Here we capture the shared_pointer of `line`,
                      //       which holds the content for `record.value()`.
                      //       It makes sure the memory block is valid until the lambda finishes.
                      [line](const RecordMetadata &metadata, const Error &error)
                      {
                          if (!error)
                          {
                              std::cout << "% Message delivered: " << metadata.toString() << std::endl;
                          }
                          else
                          {
                              std::cerr << "% Message delivery failed: " << error.message() << std::endl;
                          }
                      });

        if (line->empty())
            break;
    }

    // producer.close(); // No explicit close is needed, RAII will take care of it

    return 0;
}

// producer.close(); // No explicit close is needed, RAII will take care of it