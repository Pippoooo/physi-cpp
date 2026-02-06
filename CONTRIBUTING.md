# Contributing to physi

Thanks for contributing!

## Branches & workflow

- Target changes via feature branches: `feature/<short-desc>` or `fix/<short-desc>`.
- Open PRs targeting `main`. Do not push directly to `main`.

## Local build & tests

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
ctest --output-on-failure
```

## Formatting & checks

- Project uses clang-format. Run clang-format -i <files> prior to committing.
- CI runs build + tests; your PR must pass all checks before merge.

## PRs

- Fill the PR template.
- Add unit tests for new functionality.
- Keep changes small and focused.

## Code style

- Use C++20. Prefer constexpr and small header-only utilities.
