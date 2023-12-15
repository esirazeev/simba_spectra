#include <assert.h>
#include <cstring>
#include <format>
#include <logger.hpp>
#include <timer.hpp>

#include "file_reader/file_reader.hpp"
#include "packet/packet.hpp"
#include "types.hpp"
#include "utils.hpp"

void print_packets_in_range(uint64_t packet_from, uint64_t packet_to = std::numeric_limits<uint64_t>::max())
{
	pcap::FileReader reader("file.pcap");
	pcap::Packet packet;

	logger::println();

	timer_start();

	while (reader.readPackets() < packet_to && reader.readNextPacket(packet))
	{
		if (reader.readPackets() >= packet_from)
		{
			packet.parse();
			auto data{packet.payload()};

			logger::println(std::format("---------------------------------{}---------------------------------", reader.readPackets()));

			simba::print(simba::create<simba::MarketDataPacketHeader>(data));
			data += sizeof(simba::MarketDataPacketHeader);

			simba::print(simba::create<simba::SBEHeader>(data));
			data += sizeof(simba::SBEHeader);

			simba::print(simba::create<simba::OrderBookSnapshot_ID_17>(data));
			data += sizeof(simba::OrderBookSnapshot_ID_17);

			simba::print(simba::create<simba::RepeatingGroupDimensions>(data));
			data += sizeof(simba::RepeatingGroupDimensions);
		}
	}

	timer_stop();

	logger::println("--------------------------------------------------------------------");
	logger::println(std::format("pcap::FileReader [info]: file reading finished"));
	logger::println(std::format("pcap::FileReader [info]: read bytes  : {}", reader.readBytes()));
	logger::println(std::format("pcap::FileReader [info]: read packets: {}", reader.readPackets()));
	logger::println(std::format("reading time (ms): {}", timer_result_milliseconds()));
}

int main(int argc, const char** argv)
{
	print_packets_in_range(1, 1);

	return 0;
}
