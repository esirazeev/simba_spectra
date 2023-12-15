#ifndef SIMBA_SBE_MESSAGE_DESERIALIZER_HPP
#define SIMBA_SBE_MESSAGE_DESERIALIZER_HPP

#include <bit>
#include <span>
#include <stdexcept>

#include "simba_parser/sbe_message/types.hpp"
#include "simba_parser/utils/bytes_swap.hpp"
#include "simba_parser/utils/deserialize.hpp"

namespace simba
{
class SBEMessageDeserializer final
{
public:
	void operator()(std::span<const uint8_t> data, SBEHeader& header) const;
	void operator()(std::span<const uint8_t> data, RepeatingSectionHeader& header) const;
};
} // namespace simba

#endif // SIMBA_SBE_MESSAGE_DESERIALIZER_HPP
