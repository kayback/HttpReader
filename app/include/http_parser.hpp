#include <unordered_map>
#include <string>

class HttpAnalyzer {
public:
    HttpAnalyzer() = default;

    bool isHttpRequest(const u_char *packet, size_t length) {
        std::string data(reinterpret_cast<const char*>(packet), length);
        return data.find("GET ") != std::string::npos || data.find("POST ") != std::string::npos;
    }

    std::string getUserAgent(const u_char *packet, size_t length) {
        std::string data(reinterpret_cast<const char*>(packet), length);
        size_t pos = data.find("User-Agent: ");

        if (pos == std::string::npos) {
            return "";
        }

        std::string userAgent = data.substr(pos + 12); // Skip "User-Agent: "
        userAgent = userAgent.substr(0, userAgent.find("\r\n")); // Only up to the end of the line
        return userAgent;
    }

    void analyzePacket(const u_char *packet, size_t length) {
        if (isHttpRequest(packet, length)) {
            std::string userAgent = getUserAgent(packet, length);
            if (!userAgent.empty()) {
                userAgents[userAgent]++; // increment request count
                bandwidths[userAgent] += length; // add packet length to bandwidth
            }
        }
    }

    // Getters for userAgents and bandwidths maps
    const std::unordered_map<std::string, int>& getUserAgents() const {
        return userAgents;
    }

    const std::unordered_map<std::string, size_t>& getBandwidths() const {
        return bandwidths;
    }

private:
    std::unordered_map<std::string, int> userAgents; // User-Agent -> count
    std::unordered_map<std::string, size_t> bandwidths; // User-Agent -> bandwidth
};