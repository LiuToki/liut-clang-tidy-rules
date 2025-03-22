project(ext)

# build ext
include(ExternalProject)

# https://stackoverflow.com/questions/45414507/pass-a-list-of-prefix-paths-to-externalproject-add-in-cmake-args
string(REPLACE ";" "|" CMAKE_PREFIX_PATH_ALT_SEP "${CMAKE_PREFIX_PATH}")

ExternalProject_Add(
    llvm_project
    PREFIX          ${CMAKE_BINARY_DIR}/llvm
    GIT_REPOSITORY  https://github.com/llvm/llvm-project.git
    GIT_TAG         llvmorg-20.1.1
    SOURCE_SUBDIR   llvm
    UPDATE_COMMAND  ""
    LIST_SEPARATOR  |
    CMAKE_ARGS
        -DLLVM_ENABLE_PROJECTS=clang|clang-tools-extra
        -DCMAKE_BUILD_TYPE=Release
        -DLLVM_ENABLE_ASSERTIONS=OFF
        -DLLVM_ENABLE_LLD=OFF
        -DLLVM_CCACHE_BUILD=OFF
        -DLLVM_ENABLE_UNWIND=OFF
        -DCMAKE_INSTALL_PREFIX=${LLVM_INSTALL_DIR}
    BUILD_COMMAND   ${CMAKE_COMMAND} --build .
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install
    USES_TERMINAL_BUILD TRUE
)
