#include "parser.hpp"
#include "simba_parser/sbe_message/deserializer/deserializer.hpp"

namespace simba
{
std::vector<SBEMessage_t> SBEMessageIncrementalParser::parse(std::span<const uint8_t> data)
{
	std::vector<SBEMessage_t> messages;

	while (data.size())
	{
		const auto header{parseSBEHeader(data)};
		const auto message{parseFIXMessage(data, header.templateId)};

		messages.push_back({header, {message}});
	}

	return messages;
}

SBEHeader SBEMessageIncrementalParser::parseSBEHeader(std::span<const uint8_t>& data)
{
	SBEHeader header;
	SBEMessageDeserializer{}(data, header);
	data = data.subspan(sizeof(SBEHeader), data.size() - sizeof(SBEHeader));

	return header;
}

FIXMessage SBEMessageIncrementalParser::parseFIXMessage(std::span<const uint8_t>& data, uint16_t fixMessageType)
{
	return std::monostate{};
}
} // namespace simba
