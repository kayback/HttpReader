#include <iostream>
#include <pcap.h>
#include <string>

class PacketCapturer {
public:
    // Constructor for live capturing from a network device
    explicit PacketCapturer(const std::string& dev)
        : device(dev), handle(nullptr) {}

    // Constructor for capturing from a pcap file
    PacketCapturer(const std::string& pcap_file, [[maybe_unused]]bool flag)
        : device(""), handle(nullptr) {
        char errbuf[PCAP_ERRBUF_SIZE];
        // Open the pcap file
        handle = pcap_open_offline(pcap_file.c_str(), errbuf);
        if (handle == nullptr) {
            std::cerr << "Couldn't open pcap file " << pcap_file << ": " << errbuf << "\n";
        }
    }

    ~PacketCapturer() {
        if (handle != nullptr) {
            pcap_close(handle);
        }
    }

    // Open a live capture handle for the specified network device
    bool open() {
        // Handle is already open if we're reading from a file
        if (handle != nullptr) {
            return true; 
        }
        char errbuf[PCAP_ERRBUF_SIZE];
        // Open the live capture handle
        handle = pcap_open_live(device.c_str(), BUFSIZ, 1, 1000, errbuf);
        return handle != nullptr;
    }

    // Get the next packet from the capture handle
    bool getNextPacket(struct pcap_pkthdr *header, const u_char **packet) {
        return pcap_next_ex(handle, &header, packet) == 1;
    }

private:
    // Network device to capture from, or an empty string if capturing from a file
    std::string device;
    // Handle for capturing packets
    pcap_t *handle;
};