#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstring>
#include <vsomeip/vsomeip.hpp>
#include<thread>

struct CustomPacket {
    uint32_t sequence_number;
    uint64_t timestamp;
    std::string filename;
    uint32_t payload_length;
    std::vector<vsomeip::byte_t> payload_data;

    friend std::ostream& operator<<(std::ostream& os, const CustomPacket& packet) {
        os.write(reinterpret_cast<const char*>(&packet.sequence_number), sizeof(packet.sequence_number));
        os.write(reinterpret_cast<const char*>(&packet.timestamp), sizeof(packet.timestamp));
        uint32_t filename_length = static_cast<uint32_t>(packet.filename.size());
        os.write(reinterpret_cast<const char*>(&filename_length), sizeof(filename_length));
        os.write(packet.filename.c_str(), filename_length);
        os.write(reinterpret_cast<const char*>(&packet.payload_length), sizeof(packet.payload_length));
        os.write(reinterpret_cast<const char*>(packet.payload_data.data()), packet.payload_data.size());
        return os;
    }
};

class Server
{
public:
    Server();
    void init();
     void registerHandlers();
     void offerService();
     void start();
private:
     std::shared_ptr<vsomeip::application> app;
         // Constants declared as private members
         static const vsomeip::service_t SAMPLE_SERVICE_ID = 0x1234;
         static const vsomeip::instance_t SAMPLE_INSTANCE_ID = 0x5678;
         static const vsomeip::method_t SAMPLE_METHOD_ID = 0x0421;
          void onMessage(const std::shared_ptr<vsomeip::message>& request);
};





