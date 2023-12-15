#ifndef SIMBA_SBE_MESSAGE_PARSER_HPP
#define SIMBA_SBE_MESSAGE_PARSER_HPP

#include <span>

#include "simba_parser/sbe_message/types.hpp"

namespace simba
{
template <typename T>
concept Parsable = requires() {
	{
		T::parse(std::span<const uint8_t>{})
	} -> std::convertible_to<std::vector<SBEMessage_t>>;
};

template <Parsable T>
class SBEMessageParser
{
	[[nodiscard]] std::vector<SBEMessage_t> parse(std::span<const uint8_t> data)
	{
		return T::parse(data);
	}
};
} // namespace simba

#endif // SIMBA_SBE_MESSAGE_PARSER_HPP
