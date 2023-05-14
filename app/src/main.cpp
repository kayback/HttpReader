#include "executor.hpp"



int main(int argc, char* argv[]) {

    // PacketCapturer capturer("eth0");
    // HttpAnalyzer analyzer;
    std::shared_ptr<HttpAnalyzer> analyzer = std::make_shared<HttpAnalyzer>();
    std::unique_ptr<PacketCapturer> capturer;

    std::string pcapFile = Utils::getPcapFileName(argc, argv);
    
    if (!pcapFile.empty()) {
        capturer = std::make_unique<PacketCapturer>(pcapFile, true);
    } else {
        capturer = std::make_unique<PacketCapturer>("eth0");
    }

    if (!capturer->open()) {
        std::cerr << "Failed to open device\n";
        return 1;
    }

    std::thread analysis(Executor::analysisThread, std::ref(capturer), std::ref(analyzer));
    std::thread print;

    if (Utils::shouldPrint(argc, argv)) {
        print = std::thread(Executor::printThread, std::ref(analyzer));
    }

    analysis.join();

    if (print.joinable()) {
        print.join();
    }

    return 0;
}