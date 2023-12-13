#ifndef NETWORK_LAYER_HPP
#define NETWORK_LAYER_HPP

#include "types.hpp"

namespace pcap
{
template <typename T>
class Layer
{
public:
	virtual ~Layer() {}

	/**
	 * @brief Deserializes a network layer header from a sequence of bytes.
	 * 
   * @param data Byte sequence
   * @param size Byte sequence size
	 * 
	 * @return `true` if deserialization was successful, otherwise - `false`
	 */
	virtual bool deserialize(const uint8_t* data, uint16_t size) noexcept = 0;

	/**
	 * @brief Returns the network layer context.
	 * 
	 * @return Network layer context
	 */
	virtual LayerContext context() const noexcept = 0;

	/**
	 * @brief Returns the network layer header.
	 * 
	 * @return Network layer header
	 */
	virtual const T& header() const noexcept = 0;
};
} // namespace pcap

#endif // NETWORK_LAYER_HPP
