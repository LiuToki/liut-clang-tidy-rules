cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

include(FetchContent)

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
if(MSVC)
	set(CLANG_BINARY_URL "https://github.com/llvm/llvm-project/releases/download/llvmorg-20.1.0/clang+llvm-20.1.0-aarch64-pc-windows-msvc.tar.xz")
	set(CLANG_BINARY_HASH "SHA256=f52e40d68843ed6205858e817ed791295ef51e526037186352a1aeac4a59e51a")

	set(CLANG_BINARY_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/clang_binary-src")

	if(NOT EXISTS "${CLANG_BINARY_SOURCE_DIR}")
		message(STATUS "Clang package not found. Downloading and extracting...")
		# FetchContent を使って clang のバイナリアーカイブを取得・展開する
		FetchContent_Declare(
			clang_binary
			URL ${CLANG_BINARY_URL}
			URL_HASH ${CLANG_BINARY_HASH}
		)

		# FetchContent_MakeAvailable で configure 時に展開（展開先は clang_binary_SOURCE_DIR に設定される）
		FetchContent_MakeAvailable(clang_binary)
	else()
		message(STATUS "Clang package already exists at ${CLANG_BINARY_SOURCE_DIR}")
	endif()
	
	set(Clang_DIR "${CLANG_BINARY_SOURCE_DIR}/lib/cmake/clang")
	message(STATUS "Clang_DIR is set to: ${Clang_DIR}")
endif()

find_package(Clang REQUIRED CONFIG)
find_package(LibXml2 REQUIRED CONFIG)

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
# math
# ---------------------------------------------------------------------------

add_subdirectory(math)
