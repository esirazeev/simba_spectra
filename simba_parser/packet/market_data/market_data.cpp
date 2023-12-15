#include <cstring>

#include "market_data_packet_header.hpp"
#include "simba_spectra_parser/packet/errors/errors.hpp"
#include "simba_spectra_parser/utils/bytes_swap.hpp"

namespace simba
{
MarketDataPacketHeader::MarketDataPacketHeader(std::span<const uint8_t> data)
{
	if (data.size() < sizeof(Header)) [[unlikely]]
	{
		throw MarketDataPacketHeaderDeserialization{};
	}

	std::memcpy(&header_, data.data(), sizeof(Header));

	if constexpr (std::endian::native != std::endian::little)
	{
		header_.sequenceNumber = bswap32(header_.sequenceNumber);
		header_.size = bswap16(header_.size);
		header_.flags = bswap16(header_.flags);
		header_.time = bswap64(header_.time);
	}

	payload_ = data.subspan(sizeof(Header), data.size() - sizeof(Header));
}

uint32_t MarketDataPacketHeader::packetSequenceNumber() const noexcept
{
	return header_.sequenceNumber;
}

uint16_t MarketDataPacketHeader::packetSize() const noexcept
{
	return header_.size;
}

uint64_t MarketDataPacketHeader::packetTime() const noexcept
{
	return header_.time;
}

PacketFormat MarketDataPacketHeader::packetFormat() const noexcept
{
	return header_.flags & FlagMask::incremental_packet ? PacketFormat::incremental : PacketFormat::snapshot;
}

PacketBroadcastingType MarketDataPacketHeader::broadcastingType() const noexcept
{
	return header_.flags & FlagMask::broadcasting_online_updates ? PacketBroadcastingType::full_order_books :
								       PacketBroadcastingType::online_updates;
}

bool MarketDataPacketHeader::lastFragment() const noexcept
{
	return header_.flags & FlagMask::last_fragment;
}

bool MarketDataPacketHeader::startOfSnapshot() const noexcept
{
	return header_.flags & FlagMask::start_of_snapshot;
}

bool MarketDataPacketHeader::endOfSnapshot() const noexcept
{
	return header_.flags & FlagMask::end_of_snapshot;
}

std::span<const uint8_t> MarketDataPacketHeader::packetPayload() const noexcept
{
	return payload_;
}
} // namespace simba
