#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>


class Utils{
public:
    Utils() = delete;
    Utils(const Utils&) = delete;
    Utils(Utils&&) = delete;
    ~Utils() = delete;
    Utils& operator=(const Utils&) = delete;
    Utils& operator=(Utils&&) = delete;

    static bool shouldPrint(int argc, char* argv[]) {
        return std::find(argv, argv + argc, std::string("--print")) != argv + argc;
    }

    static std::string formatBandwidth(size_t bandwidth) {
        constexpr double kb = 1024;
        constexpr double mb = 1024 * kb;
        constexpr double gb = 1024 * mb;

        std::ostringstream out;
        out << std::fixed << std::setprecision(2);

        if (bandwidth < kb) {
            out << bandwidth << " B";
        } else if (bandwidth < mb) {
            out << bandwidth / kb << " KB";
        } else if (bandwidth < gb) {
            out << bandwidth / mb << " MB";
        } else {
            out << bandwidth / gb << " GB";
        }

        return out.str();
    }

    static std::string getPcapFileName(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) { // argv[0] is the program name
            std::string arg = argv[i];
            if (arg == "--pcap" && i + 1 < argc) {
                return argv[i + 1]; // The next argument is the pcap file name
            }
        }
        return ""; // Return an empty string if no pcap file name was found
    }
};
