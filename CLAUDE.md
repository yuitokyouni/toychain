# toychain: notes for Claude Code

## Commands
- Configure: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
- Build: `cmake --build build --parallel`
- Test: `ctest --test-dir build --output-on-failure`

## Conventions
- C++20 without compiler extensions. Keep the build at zero warnings.
- Public headers in `include/toychain/`, implementation in `src/`, tests in `tests/` (GoogleTest).
- Hash only through `toychain::sha256` (`include/toychain/hash.hpp`). Do not call CommonCrypto or OpenSSL anywhere else.

## Division of work (learning project)
- The owner writes the block structure, proof of work, and chain validation by hand.
  Do not write or complete that code unless the current message explicitly asks for it.
- Claude reviews diffs, points out bugs, proposes test cases, and explains C++ behavior.
- Build files, CI, and test scaffolding may be edited freely.
