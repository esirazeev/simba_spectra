#include "deserializer.hpp"

namespace simba
{
void SBEMessageDeserializer::operator()(std::span<const uint8_t> data, SBEHeader& header) const
{
	auto deserialized_header{deserialize<SBEHeader>(data)};

	if (!deserialized_header) [[unlikely]]
	{
		throw std::runtime_error(
			"simba::SBEMessageDeserializer [exception]: cannot deserialize Simba SBE message header - data is corrupted");
	}

	if constexpr (std::endian::native != std::endian::little)
	{
		deserialized_header->blockLength = bswap16(deserialized_header->blockLength);
		deserialized_header->templateId = bswap16(deserialized_header->templateId);
		deserialized_header->schemaId = bswap16(deserialized_header->schemaId);
		deserialized_header->version = bswap16(deserialized_header->version);
	}
}

void SBEMessageDeserializer::operator()(std::span<const uint8_t> data, RepeatingSectionHeader& header) const
{
	auto deserialized_header{deserialize<RepeatingSectionHeader>(data)};

	if (!deserialized_header) [[unlikely]]
	{
		throw std::runtime_error(
			"simba::SBEMessageDeserializer [exception]: cannot deserialize Simba SBE message Repeating Section header - data is corrupted");
	}

	if constexpr (std::endian::native != std::endian::little)
	{
		deserialized_header->blockLength = bswap16(deserialized_header->blockLength);
	}
}
} // namespace simba
