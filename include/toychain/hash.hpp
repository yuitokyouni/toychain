#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

namespace toychain {

using Hash256 = std::array<std::uint8_t, 32>;

// SHA-256 of arbitrary bytes.
// Backend: CommonCrypto on macOS, OpenSSL elsewhere. Call hashing only through
// this function so the backend stays swappable.
Hash256 sha256(std::string_view data);

// Lowercase hex encoding (64 characters for a Hash256).
std::string to_hex(const Hash256& hash);

}  // namespace toychain
