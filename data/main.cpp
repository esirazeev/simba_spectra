#include <assert.h>
#include <cstring>
#include <format>
#include <logger.hpp>
#include <timer.hpp>

#include "pcap_reader/includes/file_reader.hpp"
#include "pcap_reader/includes/packet.hpp"
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

			const auto market_data_packet_header{simba::create<simba::MarketDataPacketHeader>(data)};
			data += sizeof(simba::MarketDataPacketHeader);

			const auto flags{simba::Messageflags{
				.last_fragment = market_data_packet_header.msg_flags & 0x1 ? 1 : 0,
				.start_of_snapshot = market_data_packet_header.msg_flags & 0x2 ? 1 : 0,
				.end_of_snapshot = market_data_packet_header.msg_flags & 0x4 ? 1 : 0,
				.incremental_packet = market_data_packet_header.msg_flags & 0x8 ? 1 : 0,
				.broadcasting_online_updates = market_data_packet_header.msg_flags & 0x10 ? 1 : 0,
			}};

			if (!flags.incremental_packet && flags.start_of_snapshot == 1 && flags.end_of_snapshot == 1)
			{
				const auto sbe_header{simba::create<simba::SBEHeader>(data)};
				data += sizeof(simba::SBEHeader);

				if (sbe_header.template_id == 17)
				{
					const auto msg{simba::create<simba::OrderBookSnapshot_ID_17>(data)};
					data += sizeof(simba::OrderBookSnapshot_ID_17);

					const auto repeat_block{simba::create<simba::RepeatingGroupDimensions>(data)};
					data += sizeof(simba::RepeatingGroupDimensions);

					if (repeat_block.num_in_group > 1)
					{
						logger::println(std::format(
							"---------------------------------{}---------------------------------",
							reader.readPackets()));
						simba::print(repeat_block);

						break;
					}
				}
			}

			// logger::println(std::format("---------------------------------{}---------------------------------", reader.readPackets()));

			// simba::print(simba::create<simba::MarketDataPacketHeader>(data));
			// data += sizeof(simba::MarketDataPacketHeader);

			// simba::print(simba::create<simba::SBEHeader>(data));
			// data += sizeof(simba::SBEHeader);

			// simba::print(simba::create<simba::OrderBookSnapshot_ID_17>(data));
			// data += sizeof(simba::OrderBookSnapshot_ID_17);

			// simba::print(simba::create<simba::RepeatingGroupDimensions>(data));
			// data += sizeof(simba::RepeatingGroupDimensions);
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
	print_packets_in_range(1, 1'000);

	return 0;
}
