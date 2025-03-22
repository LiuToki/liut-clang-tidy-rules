cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

# `BUILD_EXT=ON` の場合、`ext` だけをビルドし、メインプロジェクトのビルドをスキップ
option(BUILD_EXT "Enable building external projects (LLVM)" OFF)

# ext build
if (BUILD_EXT)
	# LLVMのインストール先.
	set(LLVM_INSTALL_DIR "${CMAKE_BINARY_DIR}/llvm/install")
    add_subdirectory(ext)
	return()
endif()

# グローバルプロパティの設定（Visual Studio のフォルダ表示用）
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Vcpkg path. Not to set to envirment paths.
#set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/vcpkg)
#message(STATUS "VCPKG_ROOT: ${VCPKG_ROOT}")

# Set project settings
# プロジェクト名と実行ファイル名は分けることが多いらしい.
set(PROJECT_NAME liut-clang-tidy-rules)    # TODO:Project Name
project(${PROJECT_NAME} VERSION 0.1.0)	# Set Project Version.

# 言語の指定.
enable_language(CXX)

# Build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "vcpkg target: ${VCPKG_TARGET_TRIPLET}")
message(STATUS "vcpkg host: ${VCPKG_HOST_TRIPLET}")

# 出力先はbuild ディレクトリ.
# set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Use vcpkg toolchain file
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

# 基本戦略としてここでライブラリなど外部のものをセッティングする

# ---------------------------------------------------------------------------
# LLVM
# ---------------------------------------------------------------------------
# Clang の CMakeConfig ファイルのパス
set(Clang_DIR "${CMAKE_BINARY_DIR}/../llvm/install/lib/cmake/clang")
message(STATUS "Clang_DIR is set to: ${Clang_DIR}")

if(EXISTS "${Clang_DIR}/ClangConfig.cmake")
	message(STATUS "ClangConfig.cmake found. Configuring main project.")

	find_package(Clang REQUIRED CONFIG)
else()
	message(WARNING "ClangConfig.cmake not found. Run 'cmake --build --preset llvm-build' first, then reconfigure.")
endif()

# ---------------------------------------------------------------------------
# Boost
# ---------------------------------------------------------------------------

# If needed.
#set(Boost_USE_STATIC_LIBS        ON) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
#set(Boost_USE_STATIC_RUNTIME    OFF)

# Find libraries
# boost は最後に探しにいかないとCOMPONENTS に指定したやつが無視される(他のBoost を参照しているライブラリでFindBoost 呼ばれてBoost_LIBRARIES の設定上書きされてしまうような感じ？).
#find_package(Boost COMPONENTS log log_setup REQUIRED)	# https://cmake.org/cmake/help/git-master/module/FindBoost.html

# ---------------------------------------------------------------------------
# ビルド設定.
# ---------------------------------------------------------------------------

if(BUILD_TESTING)
	# テストフラグがある時はテストを有効化する
    enable_testing()
endif()

find_package(LibXml2 REQUIRED CONFIG)

add_subdirectory(math)

