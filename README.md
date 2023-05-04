# C23

This repository is intended for testing the new features of the upcoming C Standard.

- <https://www.open-std.org/jtc1/sc22/wg14/www/projects.html>
- <https://en.cppreference.com/w/c/compiler_support/23>
- <https://gcc.gnu.org/onlinedocs/gcc-13.1.0/gcc/>

Current compiler version: gcc 13.0.1

```console
$> make -B && ./bin/c23
```

## Features

- [ ] Attributes
  - [x] nodiscard
  - [x] maybe_unused
  - [x] fallthrough
  - [ ] deprecated
  - [ ] noreturn
- [x] u8 string literal prefix
- [x] static_assert
- [x] predefined true and false
- [x] digit separators
- [x] binary integer constants
- [x] warning directive
- [x] __has_c_attribute
- [ ] __has_include
- [ ] #elifdef, #elifndef
- [x] constexpr
- [ ] nullptr
- [ ] enhanced enumerations
- [x] unreachable macro
- [ ] ~~_BitInt~~ (not supported by gcc 13)
- [ ] ~~embed directive~~ (not supported by gcc 13)
