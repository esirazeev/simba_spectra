#ifndef SIMBA_SBE_MESSAGE_INCREMENTAL_PARSER_HPP
#define SIMBA_SBE_MESSAGE_INCREMENTAL_PARSER_HPP

#include <span>

#include "simba_parser/sbe_message/types.hpp"

namespace simba
{
class SBEMessageIncrementalParser final
{
public:
	[[nodiscard]] static std::vector<SBEMessage_t> parse(std::span<const uint8_t> data);

private:
	[[nodiscard]] static SBEHeader parseSBEHeader(std::span<const uint8_t>& data);
	[[nodiscard]] static FIXMessage parseFIXMessage(std::span<const uint8_t>& data, uint16_t fixMessageType);
};
} // namespace simba

#endif // SIMBA_SBE_MESSAGE_INCREMENTAL_PARSER_HPP
