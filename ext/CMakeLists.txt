project(ext)

# build ext
include(ExternalProject)

# https://stackoverflow.com/questions/45414507/pass-a-list-of-prefix-paths-to-externalproject-add-in-cmake-args
string(REPLACE ";" "|" CMAKE_PREFIX_PATH_ALT_SEP "${CMAKE_PREFIX_PATH}")

# LLVMのビルドに必要なPython3を検索して明示的に渡す
find_package(Python3 REQUIRED COMPONENTS Interpreter)

# LLVMの内部ビルドには Ninja を使用する（MSBuild/VS ジェネレータとの競合を回避するため）。
# CMAKE_GENERATOR / CMAKE_MAKE_PROGRAM を ExternalProject_Add に直接渡すことで、
# コンパイラ検出などのネストした cmake 呼び出しにも正しく伝搬する。
#
# Ninja が見つからない場合はビルドが失敗します。以下のいずれかでインストールしてください:
#   Windows: Visual Studio に同梱されています。
#     C:/Program Files/Microsoft Visual Studio/<version>/Community/
#       Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe
#   Linux: sudo apt install ninja-build  /  sudo dnf install ninja-build
if(WIN32)
    # Windows では Visual Studio 同梱の ninja を優先して検索する
    find_program(NINJA_EXECUTABLE ninja
        HINTS
            "$ENV{ProgramFiles}/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja"
            "$ENV{ProgramFiles}/Microsoft Visual Studio/17/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja"
            "$ENV{ProgramFiles}/Microsoft Visual Studio/18/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja"
            "$ENV{ProgramFiles}/Microsoft Visual Studio/17/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja"
        REQUIRED
    )
else()
    # Linux/macOS では PATH 上の ninja を使用する（apt/dnf などでインストール済みであること）
    find_program(NINJA_EXECUTABLE ninja REQUIRED)
endif()
message(STATUS "LLVMビルドに使用する ninja: ${NINJA_EXECUTABLE}")

ExternalProject_Add(
    llvm_project
    PREFIX          ${CMAKE_BINARY_DIR}/llvm
    GIT_REPOSITORY  https://github.com/llvm/llvm-project.git
    GIT_TAG         llvmorg-20.1.1
    SOURCE_SUBDIR   llvm
    UPDATE_COMMAND  ""
    LIST_SEPARATOR  |
    CMAKE_GENERATOR "Ninja"
    CMAKE_ARGS
        -DCMAKE_MAKE_PROGRAM=${NINJA_EXECUTABLE}
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DLLVM_ENABLE_PROJECTS=clang|clang-tools-extra
        -DCMAKE_BUILD_TYPE=Release
        -DLLVM_ENABLE_ASSERTIONS=OFF
        -DLLVM_ENABLE_LLD=OFF
        -DLLVM_CCACHE_BUILD=OFF
        -DLLVM_ENABLE_UNWIND=OFF
        -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_DIR}
        -DPython3_EXECUTABLE=${Python3_EXECUTABLE}
    BUILD_COMMAND   ${CMAKE_COMMAND} --build .
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install
    USES_TERMINAL_BUILD TRUE
)
