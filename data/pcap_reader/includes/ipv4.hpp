#ifndef NETWORK_IPV4_HPP
#define NETWORK_IPV4_HPP

#include "layer.hpp"

namespace pcap
{
namespace ipv4
{
#pragma pack(push, 1)

struct IPv4Header
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	uint8_t headerLength : 4;
	uint8_t version : 4;
#elif __BYTE_ORDER == __BIG_ENDIAN
	uint8_t version : 4;
	uint8_t headerLength : 4;
#endif
	uint8_t serviceType;
	uint16_t totalLength;
	uint16_t identification;
	uint16_t flagsOffset;
	uint8_t timeToLive;
	uint8_t protocol;
	uint16_t checksum;
	uint32_t sourceAddress;
	uint32_t destinationAddress;
};

#pragma pack(pop)

class IPv4Layer final : public Layer<IPv4Header>
{
public:
	IPv4Layer() noexcept;

	/**
	 * @brief Deserializes an IPv4 layer header from a sequence of bytes.
	 * 
   * @param data Byte sequence
   * @param size Byte sequence size
	 * 
	 * @return `true` if deserialization was successful, otherwise - `false`
	 */
	[[nodiscard]] bool deserialize(const uint8_t* data, uint16_t size) noexcept override;

	/**
	 * @brief Returns the IPv4 layer context.
	 * 
	 * @return IPv4 layer context
	 */
	[[nodiscard]] LayerContext context() const noexcept override;

	/**
	 * @brief Returns the IPv4 layer header.
	 * 
	 * @return IPv4 layer header
	 */
	[[nodiscard]] const IPv4Header& header() const noexcept override;

private:
	IPv4Header header_;
	uint16_t payloadSize_;
	const uint8_t* payload_;
};
} // namespace ipv4
} // namespace pcap

#endif // NETWORK_IPV4_HPP
