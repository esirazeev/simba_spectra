#ifndef SIMBA_PACKET_INCREMENTAL_HPP
#define SIMBA_PACKET_INCREMENTAL_HPP

#include <vector>

#include 

namespace simba
{
class IncrementalPacket final
{
public:
	IncrementalPacket(const MarketDataPacketHeader& header) noexcept;

	/**
	 * @brief Serializes a packet from a byte stream.
	 * 
	 * @return `True` if serialization was successful, otherwise - `false`
	 */
	bool serialize(const uint8_t* data, uint16_t size) noexcept;

	/**
   * @brief Returns market data packet header.
   * 
   * @return Market data packet header 
   */
	const MarketDataPacketHeader marketDataPacketHeader() const noexcept;

	/**
   * @brief Returns UTC time of the beginning of transaction processing in matching. In nanoseconds in Unix epoch, UTC timezone.
   * 
   * @return Transaction time
   */
	uint64_t transactionTime() const noexcept;

	/**
   * @brief Returns the trading session identifier.
   * 
   * @return Trading session identifier
   */
	uint32_t exchangeTradingSessionId() const noexcept;

	const std::vector<SBEHeader> messages() const noexcept;

private:
#pragma pack(push, 1)
	struct IncrementalHeader
	{
		uint64_t transactionTime;
		uint32_t exchangeTradingSessionId;
	};
#pragma pack(pop)

	MarketDataPacketHeader marketDataPacketHeader_;
	IncrementalHeader incrementalHeader_;
	std::vector<SBEHeader> messages_;
};
} // namespace simba

#endif // SIMBA_PACKET_INCREMENTAL_HPP
