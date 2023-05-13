#include <iostream>


#include <unordered_map>
#include <string>
#include <sstream>

class MyClass{
public:
    static void my_func(){
        std::cout << "test_func \n";
    }
};

// class PacketReader{
// public:

//     static void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
//         printf("Packet capture length: %d\n", pkthdr->caplen);
//         printf("Packet total length %d\n", pkthdr->len);

//         for(auto i=0; i<pkthdr->len; i++){
//             printf("%02x ", packet[i]);
//         }
//         std::cout<<"\n";
//     }
//     void read_packet(){
//         if (pcap_findalldevs(&alldevs, errbuf) == -1) {
//             printf("Device not found: %s\n", errbuf);
            
//         }
//         uint32_t i{};
//         for (auto d = alldevs; d; d = d->next) {
//             std::cout<< ++i << "  " << d->name << ": ";

//             if (d->description)
//             std::cout<<d->description << " " <<d->addresses <<" " <<std::endl;
//             else
//             std::cout<<"No description available" << std::endl;
//         }
//         handle = pcap_open_live(alldevs->name, BUFSIZ, 1, 1000, errbuf);
//         if (handle == NULL) {
//             printf("Error opening device: %s\n", errbuf);
            
//         }

//         if (pcap_loop(handle, 0, packet_handler, NULL) < 0) {
//             printf("pcap_loop error: %s\n", pcap_geterr(handle));
            
//         }

//         pcap_close(handle);
    
//     }

// private:
//     pcap_t *handle;
//     char errbuf[PCAP_ERRBUF_SIZE];
//     pcap_if_t *alldevs;
//     const char *dev;
// };



