#include "parser.hpp"
#include "simba_parser/sbe_message/deserializer/deserializer.hpp"

namespace simba
{
std::vector<SBEMessage_t> SBEMessageSnapshotParser::parse(std::span<const uint8_t> data)
{
	const auto header{parseSBEHeader(data)};

	// parse root block
	// parse repeating section header
	// if needed parse root block

	return {{header, {parseFIXMessage(data, header.templateId)}}};
}

SBEHeader SBEMessageSnapshotParser::parseSBEHeader(std::span<const uint8_t>& data)
{
	SBEHeader header;
	SBEMessageDeserializer{}(data, header);
	data = data.subspan(sizeof(SBEHeader), data.size() - sizeof(SBEHeader));

	return header;
}

RepeatingSectionHeader SBEMessageSnapshotParser::parseRepeatingSectionHeader(std::span<const uint8_t>& data)
{
	RepeatingSectionHeader header;
	SBEMessageDeserializer{}(data, header);
	data = data.subspan(sizeof(RepeatingSectionHeader), data.size() - sizeof(RepeatingSectionHeader));

	return header;
}

FIXMessage SBEMessageSnapshotParser::parseFIXMessage(std::span<const uint8_t>& data, uint16_t fixMessageType)
{
	return std::monostate{};
}
} // namespace simba
