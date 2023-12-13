#ifndef NETWORK_TYPES_HPP
#define NETWORK_TYPES_HPP

#include <cstdint>
#include <variant>

namespace pcap
{
enum class NetworkType : uint16_t
{
	UNSUPPORTED = 0x00,
	ETHERNET = 0x01,
	IP_V4 = 0x08,
	UDP = 0x11
};

struct LayerContext
{
	NetworkType type;
	uint16_t nextType;
	uint16_t payloadSize;
	const uint8_t* payload;
};
} // namespace pcap

#endif // NETWORK_TYPES_HPP
