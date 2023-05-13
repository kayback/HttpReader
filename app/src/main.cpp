#include "executor.hpp"



int main(int argc, char* argv[]) {
    
    PacketCapturer capturer("eth0");
    HttpAnalyzer analyzer;

    if (!capturer.open()) {
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