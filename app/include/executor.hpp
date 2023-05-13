#include <thread>
#include <chrono>
#include <mutex>

#include "utils.hpp"
#include "packet_reader.hpp"
#include "http_parser.hpp"

std::mutex mtx;

class Executor {
public:
    Executor() = delete;
    Executor(const Executor&) = delete;
    Executor(Executor&&) = delete;
    ~Executor() = delete;
    Executor& operator=(const Executor&) = delete;
    Executor& operator=(Executor&&) = delete;

    static void analysisThread(PacketCapturer& capturer, HttpAnalyzer& analyzer) {
        struct pcap_pkthdr header;
        const u_char *packet;

        while (capturer.getNextPacket(&header, &packet)) {
            mtx.lock();
            analyzer.analyzePacket(packet, header.len);
            mtx.unlock();
        }
    }

    static void printThread(HttpAnalyzer& analyzer) {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for 1 second

            mtx.lock();

            const auto& userAgents = analyzer.getUserAgents();
            const auto& bandwidths = analyzer.getBandwidths();

            for (const auto& pair : userAgents) {
                std::cout << "User-Agent: " << pair.first << ", Count: " << pair.second << ", Bandwidth: " << Utils::formatBandwidth(bandwidths.at(pair.first)) << "\n";
            }

            mtx.unlock();
        }
    }
};