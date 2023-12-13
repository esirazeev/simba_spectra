#ifndef NETWORK_VIEW_HPP
#define NETWORK_VIEW_HPP

#include <optional>

#include "ethernet.hpp"
#include "ipv4.hpp"
#include "types.hpp"
#include "udp.hpp"

namespace pcap
{
namespace view
{
using header_t = std::variant<ethernet::EthernetHeader, ipv4::IPv4Header, udp::UdpHeader>;

struct LayerView
{
	LayerContext context;
	header_t header;
};

/**
 * @brief Creates a network layer view.
 * 
 * @param nextType Next network layer type
 * @param payload Payload
 * @param size Payload size
 * 
 * @return View of the network layer if creation was successful, otherwise - std::nullopt
 */
[[nodiscard]] std::optional<LayerView> create(uint16_t nextType, const uint8_t* payload, uint16_t size) noexcept;
} // namespace view
} // namespace pcap

#endif // NETWORK_VIEW_HPP
