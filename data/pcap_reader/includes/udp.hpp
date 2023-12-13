#ifndef NETWORK_UDP_HPP
#define NETWORK_UDP_HPP

#include "layer.hpp"

namespace pcap
{
namespace udp
{
#pragma pack(push, 1)

struct UdpHeader
{
	uint16_t sourcePort;
	uint16_t destinationPort;
	uint16_t length;
	uint16_t checksum;
};

#pragma pack(pop)

class UdpLayer : public Layer<UdpHeader>
{
public:
	UdpLayer() noexcept;

	/**
	 * @brief Deserializes an udp layer header from a sequence of bytes.
	 * 
   * @param data Byte sequence
   * @param size Byte sequence size
	 * 
	 * @return `true` if deserialization was successful, otherwise - `false`
	 */
	[[nodiscard]] bool deserialize(const uint8_t* data, uint16_t size) noexcept override;

	/**
	 * @brief Returns the udp layer context.
	 * 
	 * @return Udp layer context
	 */
	[[nodiscard]] LayerContext context() const noexcept override;

	/**
	 * @brief Returns the udp layer header.
	 * 
	 * @return Udp layer header
	 */
	[[nodiscard]] const UdpHeader& header() const noexcept override;

private:
	UdpHeader header_;
	uint16_t payloadSize_;
	const uint8_t* payload_;
};
} // namespace udp
} // namespace pcap

#endif // NETWORK_UDP_HPP
