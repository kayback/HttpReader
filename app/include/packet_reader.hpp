#include <pcap.h>
#include <string>

class PacketCapturer {
public:
    PacketCapturer(const std::string& dev)
        : device(dev), handle(nullptr) {}

    ~PacketCapturer() {
        if (handle != nullptr) {
            pcap_close(handle);
        }
    }

    bool open() {
        char errbuf[PCAP_ERRBUF_SIZE];
        handle = pcap_open_live(device.c_str(), BUFSIZ, 1, 1000, errbuf);
        return handle != nullptr;
    }

    bool getNextPacket(struct pcap_pkthdr *header, const u_char **packet) {
        return pcap_next_ex(handle, &header, packet) == 1;
    }

private:
    std::string device;
    pcap_t *handle;
};