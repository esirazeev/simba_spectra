#include <cassert>
#include <chrono>
#include <format>
#include <logger.hpp>
#include <timer.hpp>
#include <unordered_map>

#include "pcap/file_reader/file_reader.hpp"
#include "pcap/packet/packet.hpp"
// #include "simba_spectra_parser/parser/parser.hpp"

template <typename... Args>
struct overloaded : Args...
{
	using Args::operator()...;
};

// void print_simba_snapshot_packet(const simba::SnapshotPacket& packet, uint32_t packet_id)
// {
// 	logger::println(std::format("---------------------------------{}---------------------------------", packet_id));

// 	// MarketDataPacket header
// 	logger::println("SNAPSHOT PACKET");
// 	logger::println(std::format("sequence number             [{}]", packet.marketDataPacketHeader().packetSequenceNumber()));
// 	logger::println(std::format("size                        [{}]", packet.marketDataPacketHeader().packetSize()));
// 	logger::println(std::format(
// 		"time                        [{}]", std::chrono::sys_time{std::chrono::nanoseconds{packet.marketDataPacketHeader().packetTime()}}));
// 	logger::println(std::format("last fragment               [{}]", packet.marketDataPacketHeader().lastFragment() ? "true" : "false"));
// 	logger::println(std::format("start of snapshot           [{}]", packet.marketDataPacketHeader().startOfSnapshot() ? "true" : "false"));
// 	logger::println(std::format("end of snapshot             [{}]", packet.marketDataPacketHeader().endOfSnapshot() ? "true" : "false"));
// 	// logger::println(std::format(
// 	// 	"broadcasting online updates [{}]",
// 	// 	packet.marketDataPacketHeader().broadcastingType() == simba::PacketBroadcastingType::full_order_books ? "full_order_books" :
// 	// 														"online_updates"));

// 	// SBE header
// 	logger::println(std::format("message id                  [{}]", packet.message().messageId()));
// }

// void print_simba_incremental_packet(const simba::IncrementalPacket& packet, uint32_t packet_id)
// {
// 	logger::println(std::format("---------------------------------{}---------------------------------", packet_id));

// 	// MarketDataPacketHeader
// 	logger::println("INCREMENTAL PACKET");
// 	logger::println(std::format("sequence number             [{}]", packet.marketDataPacketHeader().packetSequenceNumber()));
// 	logger::println(std::format("size                        [{}]", packet.marketDataPacketHeader().packetSize()));
// 	logger::println(std::format(
// 		"time                        [{}]", std::chrono::sys_time{std::chrono::nanoseconds{packet.marketDataPacketHeader().packetTime()}}));
// 	logger::println(std::format("last fragment               [{}]", packet.marketDataPacketHeader().lastFragment() ? "true" : "false"));
// 	// logger::println(std::format(
// 	// 	"broadcasting online updates [{}]",
// 	// 	packet.marketDataPacketHeader().broadcastingType() == simba::PacketBroadcastingType::full_order_books ? "full_order_books" :
// 	// 														"online_updates"));

// 	// IncrementalPacketHeader
// 	logger::println(std::format("transactionTime             [{}]", std::chrono::sys_time{std::chrono::nanoseconds{packet.transactionTime()}}));
// 	logger::println(std::format("exchange trading session id [{}]", packet.exchangeTradingSessionId()));

// 	// SBE headers
// 	logger::print("message ids:                ");

// 	for (auto&& message : packet.messages())
// 	{
// 		logger::print(std::format("[{}] ", message.messageId()));
// 	}

// 	logger::println("");
// }

void print_packets_in_range(uint64_t packet_from, uint64_t packet_to = std::numeric_limits<uint64_t>::max())
{
	pcap::FileReader reader("C:\\Users\\8483ed\\Documents\\vscode\\cpp\\simba_parser\\.data\\file.pcap");
	pcap::Packet packet;

	timer_start();

	while (reader.readPackets() < packet_to && reader.readNextPacket(packet))
	{
		if (reader.readPackets() >= packet_from)
		{
			if (!packet.parse() || packet.layers().size() != 3)
			{
				logger::println_error(std::format("Cannot parse packet #{}", reader.readPackets()));
				return;
			}

			// const auto result{simba::parser::parse(packet.payload())};

			// if (result)
			// {
			// 	std::visit(
			// 		overloaded{
			// 			[&](const simba::IncrementalPacket& packet) {
			// 				print_simba_incremental_packet(packet, reader.readPackets());
			// 			},
			// 			[&](const simba::SnapshotPacket& packet) {
			// 				print_simba_snapshot_packet(packet, reader.readPackets());
			// 			}},
			// 		*result);
			// }
			// else
			// {
			// 	logger::println(
			// 		std::format("---------------------------------{}---------------------------------", reader.readPackets()));
			// 	logger::println_error(std::format("ERROR: {}", result.error()));
			// }
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
	print_packets_in_range(std::stoi(argv[1]), std::stoi(argv[2]));

	return 0;
}
