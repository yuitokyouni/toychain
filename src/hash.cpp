#include "toychain/hash.hpp"

#include <limits>
#include <stdexcept>

#if defined(__APPLE__)
#include <CommonCrypto/CommonDigest.h>
#else
#include <openssl/evp.h>
#endif

namespace toychain {

Hash256 sha256(std::string_view data) {
  Hash256 out{};
#if defined(__APPLE__)
  static_assert(CC_SHA256_DIGEST_LENGTH == std::tuple_size_v<Hash256>);
  // CC_LONG is 32-bit: refuse inputs it cannot represent instead of truncating.
  if (data.size() > std::numeric_limits<CC_LONG>::max()) {
    throw std::length_error("sha256: input larger than 4 GiB");
  }
  CC_SHA256(data.data(), static_cast<CC_LONG>(data.size()), out.data());
#else
  unsigned int len = 0;
  if (EVP_Digest(data.data(), data.size(), out.data(), &len, EVP_sha256(), nullptr) != 1 ||
      len != out.size()) {
    throw std::runtime_error("sha256: EVP_Digest failed");
  }
#endif
  return out;
}

std::string to_hex(const Hash256& hash) {
  static constexpr char kDigits[] = "0123456789abcdef";
  std::string s;
  s.reserve(hash.size() * 2);
  for (std::uint8_t b : hash) {
    s.push_back(kDigits[b >> 4]);
    s.push_back(kDigits[b & 0x0F]);
  }
  return s;
}

}  // namespace toychain
