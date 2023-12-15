#include <chrono>
#include <format>

#include "logger.hpp"
#include "utils.hpp"

namespace simba
{
template <>
MarketDataPacketHeader create(const uint8_t* data) noexcept
{
	MarketDataPacketHeader header;
	std::memcpy(&header, data, sizeof(MarketDataPacketHeader));

	if constexpr (std::endian::native != std::endian::little)
	{
		header.msg_seq_num = bswap32(header.msg_seq_num);
		header.msg_size = bswap16(header.msg_size);
		header.msg_flags = bswap16(header.msg_flags);
		header.msg_time = bswap64(header.msg_time);
	}

	return header;
}

template <>
IncrementalPacketHeader create(const uint8_t* data) noexcept
{
	IncrementalPacketHeader header;
	std::memcpy(&header, data, sizeof(IncrementalPacketHeader));

	if constexpr (std::endian::native != std::endian::little)
	{
		header.transact_time = bswap64(header.transact_time);
		header.exchange_trading_session_id = bswap32(header.exchange_trading_session_id);
	}

	return header;
}

template <>
SBEHeader create(const uint8_t* data) noexcept
{
	SBEHeader header;
	std::memcpy(&header, data, sizeof(SBEHeader));

	if constexpr (std::endian::native != std::endian::little)
	{
		header.block_length = bswap16(header.block_length);
		header.template_id = bswap16(header.template_id);
		header.schema_id = bswap16(header.schema_id);
		header.version = bswap16(header.version);
	}

	return header;
}

template <>
RepeatingGroupDimensions create(const uint8_t* data) noexcept
{
	RepeatingGroupDimensions header;
	std::memcpy(&header, data, sizeof(RepeatingGroupDimensions));

	if constexpr (std::endian::native != std::endian::little)
	{
		header.block_length = bswap16(header.block_length);
	}

	return header;
}

template <>
OrderBookSnapshot_ID_17 create(const uint8_t* data) noexcept
{
	OrderBookSnapshot_ID_17 msg;
	std::memcpy(&msg, data, sizeof(OrderBookSnapshot_ID_17));

	if constexpr (std::endian::native != std::endian::little)
	{
		msg.security_id = bswap32(msg.security_id);
		msg.last_msg_seq_num_processed = bswap32(msg.last_msg_seq_num_processed);
		msg.rpt_seq = bswap32(msg.rpt_seq);
		msg.exchange_trading_session_id = bswap32(msg.exchange_trading_session_id);
	}

	return msg;
}

template <>
void print(const MarketDataPacketHeader& header) noexcept
{
	const Messageflags flags{
		.last_fragment = header.msg_flags & 0x1 ? 1 : 0,
		.start_of_snapshot = header.msg_flags & 0x2 ? 1 : 0,
		.end_of_snapshot = header.msg_flags & 0x4 ? 1 : 0,
		.incremental_packet = header.msg_flags & 0x8 ? 1 : 0,
		.broadcasting_online_updates = header.msg_flags & 0x10 ? 1 : 0,
	};

	logger::println("Market Data Packet Header");
	logger::println(std::format("\tmsg_seq_num                 [{}]", header.msg_seq_num));
	logger::println(std::format("\tmsg_size                    [{}]", header.msg_size));
	logger::println(std::format("\tlast_fragment               [{}]", flags.last_fragment));
	logger::println(std::format("\tstart_of_snapshot           [{}]", flags.start_of_snapshot));
	logger::println(std::format("\tend_of_snapshot             [{}]", flags.end_of_snapshot));
	logger::println(std::format("\tincremental_packet          [{}]", flags.incremental_packet));
	logger::println(std::format("\tbroadcasting_online_updates [{}]", flags.broadcasting_online_updates));
	logger::println(std::format("\tmsg_time                    [{}]", std::chrono::sys_time{std::chrono::nanoseconds{header.msg_time}}));
}

template <>
void print(const IncrementalPacketHeader& header) noexcept
{
	logger::println("Incremental Packet Header");
	logger::println(std::format("\ttransact_time               [{}]", std::chrono::sys_time{std::chrono::nanoseconds{header.transact_time}}));
	logger::println(std::format("\texchange_trading_session_id [{}]", header.exchange_trading_session_id));
}

template <>
void print(const SBEHeader& header) noexcept
{
	logger::println("SBE Header");
	logger::println(std::format("\tblock_length [{}]", header.block_length));
	logger::println(std::format("\ttemplate_id  [{}]", header.template_id));
	logger::println(std::format("\tschema_id    [{}]", header.schema_id));
	logger::println(std::format("\tversion      [{}]", header.version));
}

template <>
void print(const RepeatingGroupDimensions& header) noexcept
{
	logger::println("Repeating Group Dimensions");
	logger::println(std::format("\tblock_length [{}]", header.block_length));
	logger::println(std::format("\tnum_in_group  [{}]", static_cast<uint16_t>(header.num_in_group)));
}

template <>
void print(const OrderBookSnapshot_ID_17& msg) noexcept
{
	logger::println("Order Book Snapshot ID_17");
	logger::println(std::format("\tsecurity_id                 [{}]", msg.security_id));
	logger::println(std::format("\tlast_msg_seq_num_processed  [{}]", msg.last_msg_seq_num_processed));
	logger::println(std::format("\trpt_seq                     [{}]", msg.rpt_seq));
	logger::println(std::format("\texchange_trading_session_id [{}]", msg.exchange_trading_session_id));
}
} // namespace simba
