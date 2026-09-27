# toychain

[![ci](https://github.com/yuitokyouni/toychain/actions/workflows/ci.yml/badge.svg)](https://github.com/yuitokyouni/toychain/actions/workflows/ci.yml)

A minimal proof-of-work blockchain in C++20, written from scratch to see how
hash-linked blocks, proof of work, and chain validation fit together.

## Scope

- **Block**: index, timestamp, transactions, previous block hash, nonce
- **Proof of work**: find a nonce whose block hash meets a difficulty target
- **Validation**: changing any past transaction makes validation fail, shown by a test

Out of scope: networking, digital signatures, consensus between nodes, and
anything with real value. This is not a cryptocurrency.

## Build and test

Requires CMake 3.24+ and a C++20 compiler. SHA-256 comes from CommonCrypto on
macOS (part of the OS) and from OpenSSL elsewhere (`libssl-dev` on Ubuntu).

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Debug builds run with AddressSanitizer and UndefinedBehaviorSanitizer.
Use `-DCMAKE_BUILD_TYPE=Release` (in a separate build directory) when timing proof of work.

## Layout

```
include/toychain/   public headers
src/                implementation
tests/              GoogleTest suites
```

## License

MIT
