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
### vcpkg
```
$ bootstrap-vcpkg.bat -disableMetrics
$ vcpkg install libxml2:x64-windows
```

### CMake
- CMake >= 3.21
```
$ cmake --build --preset <preset_name>
```

- otherwise
```
$ cmake --preset <preset_name>
$ cmake --build --preset <preset_name>
```

## Author
[LiuToki](https://github.com/LiuToki)

## License
[MIT](./LICENCE)

# 開発者向け
## テストについて
テストはルールがうまく機能するかどうかをチェックするために使う

## LLVM
バージョンのタグでリポジトリを固定する

    cd llvm-project
    git fetch --tags
    git checkout llvmorg-20.1.0
    cd ..
    git add llvm-project
    git commit -m "moved llvm-project at llvmorg-20.1.0"
    git push