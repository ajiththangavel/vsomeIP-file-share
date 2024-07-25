#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <vsomeip/vsomeip.hpp>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unordered_set>
#include <vector>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421

struct CustomFilePacket {
    uint32_t sequence_number;
    uint64_t timestamp;
    uint32_t filename_length;
    std::string filename;
    std::string filetype;
    uint32_t payload_length;
    std::vector<vsomeip::byte_t> payload_data;
};

class Client
{
public:
    Client();
    void init();
    void registerHandlers();
    void requestService();
    void start();

private:
    std::shared_ptr<vsomeip::application> app;
    std::mutex mutex;
    std::condition_variable condition;
    std::ofstream output_file;  // Open the output file in append mode
    std::string received_filename; // Store the received filename
    std::unordered_set<uint32_t> received_packets;
    bool service_available;  // Flag to track service availability
    //////////////////////////////////////////////////////////////

    
    

    void run();
    void sendRequest();  // Add the declaration for the sendRequest method
    void onMessage(const std::shared_ptr<vsomeip::message>& response);
    void onAvailability(bool available);
    void deserializeCustomFilePacket(CustomFilePacket& packet, const std::vector<vsomeip::byte_t>& serialized_data);
    bool isAllPacketsReceived() const;
    uint16_t total_data_received = 0;
    std::string current_filename; // Tracks the current file being written
};


#endif // CLIENT_H


