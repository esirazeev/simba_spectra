#ifndef TYPES_HPP
#define TYPES_HPP

#include <bit>
#include <cstdint>
#include <cstring>

#include "utils/bytes_swap.hpp"

namespace simba
{
struct Messageflags
{
	// 0x1  - message fragmentation flag (LastFragment): 0 - it is not the last fragment of a fragmented message; 1 - last fragment of a fragmented message or the message is not fragmented.
	uint8_t last_fragment : 1;

	// 0x2  - flag of the first message in the snapshot for the instrument (StartOfSnapshot);
	uint8_t start_of_snapshot : 1;

	// 0x4  - flag of the last message in the snapshot for the instrument (EndOfSnapshot);
	uint8_t end_of_snapshot : 1;

	// 0x8  - flag of the 'IncrementalPacket': 0 - flag of the 'Snapshot' packet, 1 - flag of the 'Incremental' packet.
	uint8_t incremental_packet : 1;

	// 0x10 - flag PossDupFlag: 0 - flag of broadcasting online updates, 1 - flag of broadcasting full order-books in the form of Incremental packages.
	uint8_t broadcasting_online_updates : 1;
};

#pragma pack(push, 1)
struct MarketDataPacketHeader
{
	uint32_t msg_seq_num;
	uint16_t msg_size;
	uint16_t msg_flags;
	uint64_t msg_time;
};

struct SBEHeader
{
	uint16_t block_length;
	uint16_t template_id;
	uint16_t schema_id;
	uint16_t version;
};

struct IncrementalPacketHeader
{
	uint64_t transact_time;
	uint32_t exchange_trading_session_id;
};

struct RepeatingGroupDimensions
{
	uint16_t block_length;
	uint8_t num_in_group;
};

struct OrderBookSnapshot_ID_17
{
	uint32_t security_id;
	uint32_t last_msg_seq_num_processed;
	uint32_t rpt_seq;
	uint32_t exchange_trading_session_id;
};
#pragma pack(pop)
} // namespace simba
#endif // TYPES_HPP
