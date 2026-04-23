<h1 align="center">liut-clang-tidy-rules</h1>

<div align="center">
    <strong>clang-tidy rules for Liu Toki.</strong>
</div>

<br/>

<div align="center">
    <sub>
        C++ rules for static analysis.
    </sub>
</div>

<br/>

## Table of Contents
- [Table of Contents](#table-of-contents)
- [Installation](#installation)
- [Features](#features)
- [Build](#build)
- [Author](#author)
- [License](#license)

## Installation
共有ライブラリをビルドして各ビルドツールでいい感じに使う

## Features
- Math Checks

## Build
- CMake >= 3.24

### Windows
```
# vcpkg（初回のみ・libxml2はvcpkg.jsonから自動インストール）
$ libs/vcpkg/bootstrap-vcpkg.bat -disableMetrics
# external（LLVMのビルド・初回のみ・時間がかかります）
$ cmake --preset windows-ext
$ cmake --build --preset windows-ext
# debug
$ cmake --preset windows-x64-debug
$ cmake --build --preset windows-x64-debug
# test
$ cmake --preset windows-x64-debug-test
$ cmake --build --preset windows-x64-debug-test
$ ctest --preset test-windows-x64
```
### Linux
```
# vcpkg（初回のみ・libxml2はvcpkg.jsonから自動インストール）
$ libs/vcpkg/bootstrap-vcpkg.sh -disableMetrics
# external（LLVMのビルド・初回のみ・時間がかかります）
$ cmake --preset linux-ext
$ cmake --build --preset linux-ext
# debug
$ cmake --preset linux-x64-debug
$ cmake --build --preset linux-x64-debug
# test
$ cmake --preset linux-x64-debug-test
$ cmake --build --preset linux-x64-debug-test
$ ctest --preset test-linux-x64
```

## Author
[LiuToki](https://github.com/LiuToki)

## License
[MIT](./LICENCE)

# 開発者向け
## テストについて
テストはルールがうまく機能するかどうかをチェックするために使う
