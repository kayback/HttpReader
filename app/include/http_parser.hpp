#include <unordered_map>
#include <string>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>

class HttpAnalyzer {
public:
    HttpAnalyzer() = default;

    // This function checks whether a packet is an HTTP request.
    bool isHttpRequest(const u_char *packet) {
        auto eth_header = reinterpret_cast<const ether_header*>(packet);

        // If the packet isn't IP, it can't be an HTTP request
        if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) {
            return false;
        }
        auto ip_header = reinterpret_cast<const ip*>(packet + ETHER_HDR_LEN);

        // If the packet isn't TCP, it can't be an HTTP request
        if (ip_header->ip_p != IPPROTO_TCP) {
            return false;
        }
        auto tcp_header = reinterpret_cast<const tcphdr*>(reinterpret_cast<const u_char*>(ip_header) + (ip_header->ip_hl << 2));

        // If the TCP port isn't 80, it can't be an HTTP request
        if (ntohs(tcp_header->source) == 80 || ntohs(tcp_header->dest) == 80) {
            int tcp_header_size = tcp_header->th_off * 4;
            if (tcp_header_size < sizeof(struct tcphdr)) {
                return false;
            }

            int packet_size = ntohs(ip_header->ip_len);
            // Perform some length checks to avoid parsing errors
            if (packet_size < ETHER_HDR_LEN + (ip_header->ip_hl << 2) + tcp_header_size) {
                return false;
            }
            // Get a pointer to the potential HTTP data and its length
            const u_char* http_data = packet + ETHER_HDR_LEN + (ip_header->ip_hl << 2) + tcp_header_size;
            int http_data_len = packet_size - ETHER_HDR_LEN - (ip_header->ip_hl << 2) - tcp_header_size;

            std::string_view http_data_view{reinterpret_cast<const char*>(http_data), static_cast<size_t>(http_data_len)};

            std::array<std::string_view, 6> http_headers {
                "GET ", "POST ", "PUT ", "HTTP/1.0 ", "HTTP/1.1 ", "HTTP/2.0 "
            };
            // Check if the packet data starts with any of the HTTP headers
            for(const auto& header : http_headers) {
                if(http_data_view.substr(0, header.size()) == header) {
                    return true;
                }
            }
        }
        return false;
    }

    // This function extracts the User-Agent information from the packet
    std::string getUserAgent(const u_char *packet, size_t length) {
        std::string_view data(reinterpret_cast<const char*>(packet), std::min(length, size_t(1024)));
        size_t pos = data.find("User-Agent: ");
        // If there is no User-Agent field, return an empty string
        if (pos == std::string_view::npos) {
            return "";
        }

        // Skip "User-Agent: " and extract the User-Agent value
        std::string_view userAgent = data.substr(pos + 12);
        // Only up to the end of the line
        userAgent = userAgent.substr(0, userAgent.find("\r\n"));
        return std::string(userAgent);
    }

    // This function analyzes the packet
    void analyzePacket(const u_char *packet, size_t length) {
        // First, check if the packet is an HTTP request
        if (isHttpRequest(packet)) {
            std::string userAgent = getUserAgent(packet, length);
            // If found a User-Agent, update statistics
            if (!userAgent.empty()) {
                // increment request count
                userAgents[userAgent]++;
                // add packet length to bandwidth
                bandwidths[userAgent] += length; 
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
    // Map to store the number of requests per User-Agent
    std::unordered_map<std::string, int> userAgents;
    // Map to store the total bandwidth per User-Agent
    std::unordered_map<std::string, size_t> bandwidths;
};