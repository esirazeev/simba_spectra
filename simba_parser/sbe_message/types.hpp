#ifndef SIMBA_SBE_MESSAGE_TYPES_HPP
#define SIMBA_SBE_MESSAGE_TYPE_HPP

#include <cstdint>
#include <utility>
#include <variant>
#include <vector>

namespace simba
{
#pragma pack(push, 1)
struct SBEHeader
{
	uint16_t blockLength;
	uint16_t templateId;
	uint16_t schemaId;
	uint16_t version;
};

struct RepeatingSectionHeader
{
	uint16_t blockLength;
	uint8_t numInGroup;
};
#pragma pack(pop)

using FIXMessage = std::variant<std::monostate>;
using SBEMessage_t = std::pair<SBEHeader, std::vector<FIXMessage>>;
} // namespace simba

#endif // SIMBA_MESSAGE_TYPE_HPP
