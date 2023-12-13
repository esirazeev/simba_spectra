#ifndef NETWORK_ETHERNET_HPP
#define NETWORK_ETHERNET_HPP

#include "layer.hpp"

namespace pcap
{
namespace ethernet
{
#pragma pack(push, 1)

struct EthernetHeader
{
	uint8_t destination[6];
	uint8_t source[6];
	uint16_t type;
};

#pragma pack(pop)

class EthernetLayer final : public Layer<EthernetHeader>
{
public:
	EthernetLayer() noexcept;

	/**
	 * @brief Deserializes an ethernet layer header from a sequence of bytes.
	 * 
   * @param data Byte sequence
   * @param size Byte sequence size
	 * 
	 * @return `true` if deserialization was successful, otherwise - `false`
	 */
	[[nodiscard]] bool deserialize(const uint8_t* data, uint16_t size) noexcept override;

	/**
	 * @brief Returns the ethernet layer context.
	 * 
	 * @return Ethernet layer context
	 */
	[[nodiscard]] LayerContext context() const noexcept override;

	/**
	 * @brief Returns the ethernet layer header.
	 * 
	 * @return Ethernet layer header
	 */
	[[nodiscard]] const EthernetHeader& header() const noexcept override;

private:
	EthernetHeader header_;
	uint16_t payloadSize_;
	const uint8_t* payload_;
};
} // namespace ethernet
} // namespace pcap

#endif // NETWORK_ETHERNET_HPP
