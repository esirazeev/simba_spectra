#ifndef PCAP_PACKET_HPP
#define PCAP_PACKET_HPP

#include <cstdint>
#include <vector>

#include "view.hpp"
#include "raw_buffer.hpp"

namespace pcap
{
class Packet final
{
public:
	Packet() noexcept;
	Packet(const Packet&) = delete;
	Packet(Packet&&) noexcept;
	Packet& operator=(const Packet&) = delete;
	Packet& operator=(Packet&&) noexcept;
	~Packet() = default;

	/**
	 * @brief Fills packet.
	 * 
	 * @param timestampNanoSec Timestamp `nanoseconds`
	 * @param linkLayerType Link layer type
	 * @param buffer Raw data buffer
	 * 
	 * @return `true` if the package was successfully filled, otherwise - `false`
	 */
	void fill(uint64_t timestampNanoSec, uint32_t linkLayerType, const RawBuffer& buffer);

	/**
	 * @brief Fills packet.
	 * 
	 * @param timestampNanoSec Timestamp `nanoseconds`
	 * @param linkLayerType Link layer type
	 * @param buffer Raw data buffer
	 * 
	 * @return `true` if the package was successfully filled, otherwise - `false`
	 */
	void fill(uint64_t timestampNanoSec, uint32_t linkLayerType, RawBuffer&& buffer);

	/**
	 * @brief Returns packet timestamp.
	 * 
	 * @return Packet timestamp `nanoseconds`
	 */
	uint64_t timestamp() const noexcept;

	/**
	 * @brief Returns packet size.
	 * 
	 * @return Packet size
	 */
	uint16_t size() const noexcept;

	/**
	 * @brief Parses packet layers.
	 */
	void parse();

	/**
	 * @brief Returns first network layer view.
	 * 
	 * @return First network layer view
	 */
	const view::LayerView* firstNetworkLayerView() const noexcept;

	/**
	 * @brief Returns last network layer view. 
	 * 
	 * @return Last network layer view
	 */
	const view::LayerView* lastNetworkLayerView() const noexcept;

	/**
	 * @brief Returns network layer views.
	 * 
	 * @return Network layer views
	 */
	const std::vector<view::LayerView>& networkLayerViews() const noexcept;

	/**
	 * @brief Returns packet payload.
	 * 
	 * @return Packet payload 
	 */
	const uint8_t* payload() const noexcept;

	/**
	 * @brief Returns packet payload size.
	 * 
	 * @return Packet payload size
	 */
	uint16_t payloadSize() const noexcept;

private:
	RawBuffer buffer_;
	std::vector<view::LayerView> networkLayerViews_;
	uint16_t payloadSize_;
	uint32_t linkLayerType_;
	uint64_t timestampNanoSec_;
	const uint8_t* payload_;
};
} // namespace pcap

#endif
