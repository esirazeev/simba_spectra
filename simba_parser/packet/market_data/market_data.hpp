#ifndef SIMBA_PACKET_HEADER_MARKET_DATA_HPP
#define SIMBA_PACKET_HEADER_MARKET_DATA_HPP

#include <span>

#include "types.hpp"

namespace simba
{
class MarketDataPacketHeader final
{
public:
	MarketDataPacketHeader(std::span<const uint8_t> data) noexcept;

	/**
	 * @brief Returns the packet sequence number. A unique number is given to each packet sent.
	 * 
	 * @return Packet sequence number
	 */
	uint32_t packetSequenceNumber() const noexcept;

	/**
	 * @brief Returns the packet size. The length of the entire message in bytes, including the length of this packet header.
	 * 
	 * @return Packet size
	 */
	uint16_t packetSize() const noexcept;

	/**
	 * @brief Returns UTC time when the packet was sent by the gateway. In nanoseconds with Unix epoch, UTC timezone.
	 * 
	 * @return Packet time 
	 */
	uint64_t packetTime() const noexcept;

	/**
	 * @brief Returns the packet format type.
	 * 
	 * @return Packet format type
	 */
	PacketFormat packetFormat() const noexcept;

	/**
	 * @brief Returns the packet broadcasting type.
	 * 
	 * @return Packet broadcasting type
	 */
	PacketBroadcastingType broadcastingType() const noexcept;

	/**
	 * @brief Specifies the message fragmentation flag.
	 * 
	 * @return `True` if this is the last fragment of a fragmented message or the message is not fragmented, otherwise - `false`
	 */
	bool lastFragment() const noexcept;

	/**
	 * @brief Specifies the flag of the first message in the snapshot for the instrument.
	 * 
	 * @return `True` if this is the first message in the snapshot for the instrument, otherwise - `false`
	 */
	bool startOfSnapshot() const noexcept;

	/**
	 * @brief Specifies the flag of the last message in the snapshot for the instrument.
	 * 
	 * @return `True` if this is the last message in the snapshot for the instrument, otherwise - `false`
	 */
	bool endOfSnapshot() const noexcept;

	/**
	 * @brief Returns the packet payload.
	 * 
	 * @return Packet payload
	 */
	std::span<const uint8_t> packetPayload() const noexcept;

private:
	enum FlagMask : uint8_t
	{
		last_fragment = 0x1,
		start_of_snapshot = 0x2,
		end_of_snapshot = 0x4,
		incremental_packet = 0x8,
		broadcasting_online_updates = 0x10
	};

#pragma pack(push, 1)
	struct Header
	{
		uint32_t sequenceNumber;
		uint16_t size;
		uint16_t flags;
		uint64_t time;
	};
#pragma pack(pop)

	Header header_;
	std::span<const uint8_t> payload_;
};
} // namespace simba

#endif // SIMBA_PACKET_HEADER_MARKET_DATA_HPP
