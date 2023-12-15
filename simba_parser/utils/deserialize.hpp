#ifndef SIMBA_UTILS_DESERIALIZE_HPP
#define SIMBA_UTILS_DESERIALIZE_HPP

#include <cstdint>
#include <cstring>
#include <optional>
#include <span>

/**
 * @brief Deserializes an object from a data stream.
 * 
 * @param data Data stream
 * @return Object, if deserialization was successful, otherwise - std::nullopt 
 */
template <typename T>
[[nodiscard]] std::optional<T> deserialize(std::span<const uint8_t> data) noexcept
{
	if (data.size() < sizeof(T)) [[unlikely]]
	{
		return {};
	}

	T obj;
	std::memcpy(&obj, data.data(), sizeof(T));

	return obj;
}

#endif // SIMBA_UTILS_DESERIALIZE_HPP
