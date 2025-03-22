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
- CMake >= 3.21

### Windows
```
# vcpkg
$ bootstrap-vcpkg.bat -disableMetrics
$ vcpkg install libxml2:x64-windows
# external
$ cmake --preset windows-ext
$ cmake --build --preset windows-ext
# debug
$ cmake --preset windows-x64-debug
$ cmake --build --preset windows-x64-debug
# test
$ cmake --preset windows-x64-debug-test
$ ctest --preset test-windows-x64   
```
### Linux
```
# vcpkg
$ bootstrap-vcpkg.bat -disableMetrics
$ vcpkg install libxml2:x64-linux
# external
$ cmake --preset linux-ext
$ cmake --build --preset linux-ext
# debug
$ cmake --preset linux-x64-debug
$ cmake --build --preset linux-x64-debug
```

## Author
[LiuToki](https://github.com/LiuToki)

## License
[MIT](./LICENCE)

# 開発者向け
## テストについて
テストはルールがうまく機能するかどうかをチェックするために使う
