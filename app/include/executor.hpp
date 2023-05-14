#include <thread>
#include <chrono>
#include <mutex>

#include "utils.hpp"
#include "packet_reader.hpp"
#include "http_parser.hpp"

// Define a global mutex for thread-safe operations
std::mutex mtx;

// Define an Executor class which will handle packet analysis and printing of results
class Executor {
public:
    // Delete all default constructors and assignment operators to prevent instantiation or copying
    Executor() = delete;
    Executor(const Executor&) = delete;
    Executor(Executor&&) = delete;
    ~Executor() = delete;
    Executor& operator=(const Executor&) = delete;
    Executor& operator=(Executor&&) = delete;

    // Define a thread function for packet analysis
    static void analysisThread(std::unique_ptr<PacketCapturer>& capturer, std::shared_ptr<HttpAnalyzer>& analyzer) {
        struct pcap_pkthdr header;
        const u_char *packet;

        // While there are packets to analyze
        while (capturer->getNextPacket(&header, &packet)) {
            // Lock the mutex to ensure thread-safety
            std::lock_guard<std::mutex> lock(mtx);
            // Analyze the packet
            analyzer->analyzePacket(packet, header.len);
        }
    }

    // Define a thread function for printing analysis results
    static void printThread(std::shared_ptr<HttpAnalyzer>& analyzer) {
        // Continuously print results every second
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for 1 second

            // Lock the mutex to ensure thread-safety
            std::lock_guard<std::mutex> lock(mtx);

            const auto& userAgents = analyzer->getUserAgents();
            const auto& bandwidths = analyzer->getBandwidths();

            // Print User-Agent, request count, and bandwidth for each User-Agent
            for (const auto& pair : userAgents) {
                std::cout << "User-Agent: " << pair.first << ", Count: " << pair.second << ", Bandwidth: " << Utils::formatBandwidth(bandwidths.at(pair.first)) << "\n";
            }
        }
    }
};