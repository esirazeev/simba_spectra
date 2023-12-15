#include <bit>
#include <cstring>

#include "../../utils/bytes_swap.hpp"
#include "incremental.hpp"

namespace simba
{
IncrementalPacket::IncrementalPacket(const MarketDataPacketHeader& header) noexcept : marketDataPacketHeader_(header) {}

bool IncrementalPacket::serialize(const uint8_t* data, uint16_t size) noexcept
{
	if (size < sizeof(IncrementalHeader)) [[unlikely]]
	{
		return false;
	}

	std::memcpy(&incrementalHeader_, data, sizeof(IncrementalHeader));

	if constexpr (std::endian::native != std::endian::little)
	{
		incrementalHeader_.transactionTime = bswap64(incrementalHeader_.transactionTime);
		incrementalHeader_.exchangeTradingSessionId = bswap32(incrementalHeader_.exchangeTradingSessionId);
	}

	int16_t messagesDataSize{size - sizeof(IncrementalHeader)};
	auto messagesData{data + sizeof(IncrementalHeader)};

	do
	{
		SBEHeader header;

		if (!header.serialize(messagesData, messagesDataSize)) [[unlikely]]
		{
			return false;
		}

		messages_.push_back(header);

		const auto messageSize{header.size() + header.messageRootBlockSize()};
		messagesDataSize -= messageSize;
		messagesData += messageSize;
	}
	while (messages_.back().messageRootBlockSize() && messagesDataSize > messages_.back().size());

	return true;
}

const MarketDataPacketHeader IncrementalPacket::marketDataPacketHeader() const noexcept
{
	return marketDataPacketHeader_;
}

uint64_t IncrementalPacket::transactionTime() const noexcept
{
	return incrementalHeader_.transactionTime;
}

uint32_t IncrementalPacket::exchangeTradingSessionId() const noexcept
{
	return incrementalHeader_.exchangeTradingSessionId;
}

const std::vector<SBEHeader> IncrementalPacket::messages() const noexcept
{
	return messages_;
}
} // namespace simba
