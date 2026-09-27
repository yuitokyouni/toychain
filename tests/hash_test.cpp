#include <gtest/gtest.h>

#include "toychain/hash.hpp"

using toychain::sha256;
using toychain::to_hex;

// Known-answer tests (NIST SHA-256 test vectors).
TEST(Sha256, EmptyInput) {
  EXPECT_EQ(to_hex(sha256("")),
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST(Sha256, Abc) {
  EXPECT_EQ(to_hex(sha256("abc")),
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
}

TEST(Sha256, TwoBlockMessage) {
  EXPECT_EQ(to_hex(sha256("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq")),
            "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}

// One changed character gives an unrelated hash: the property that makes
// tampering with a past block detectable.
TEST(Sha256, OneCharacterChangesTheHash) {
  EXPECT_NE(sha256("alice->bob:10"), sha256("alice->bob:11"));
}
