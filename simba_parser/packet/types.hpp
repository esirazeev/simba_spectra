#ifndef SIMBA_PACKET_TYPES_HPP
#define SIMBA_PACKET_TYPES_HPP

#include <cstdint>

namespace simba
{
enum PacketFormat : uint8_t
{
	snapshot,
	incremental
};

enum PacketBroadcastingType : uint8_t
{
	online_updates,
	full_order_books
};

#pragma pack(push, 1)
struct MarketDataPacketHeader
{
	uint32_t sequenceNumber;
	uint16_t size;
	uint16_t flags;
	uint64_t time;
};

struct IncrementalHeader
{
	uint64_t transactionTime;
	uint32_t exchangeTradingSessionId;
};
#pragma pack(pop)
} // namespace simba

#endif // SIMBA_PACKET_TYPES_HPP
