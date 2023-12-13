#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"

namespace simba
{
template <typename T>
T create(const uint8_t* data) noexcept;

template <typename T>
void print(const T& header) noexcept;
} // namespace simba

#endif // UTILS_HPP
