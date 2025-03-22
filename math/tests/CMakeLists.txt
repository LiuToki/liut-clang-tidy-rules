# Boostを探す
#find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# テスト実行ファイルを作成
#add_executable(feature1_test feature1_test.cpp)

# テスト実行ファイルにライブラリをリンク
# target_link_libraries(feature1_test
#     Boost::unit_test_framework
#     # 他の必要なライブラリもここに追加
# )

# テスト用にパイソンスクリプトをパスの通る場所に設置する(他のとこでもいいかも).

# テストを登録
if(MSVC)
	set(MATH_DLL_PATH "${CMAKE_BINARY_DIR}/bin/Debug/math_Check_${LLVM_VERSION_MAJOR}.dll")
else()
	set(MATH_DLL_PATH "${CMAKE_BINARY_DIR}/bin/Debug/math_Check_${LLVM_VERSION_MAJOR}.so")
endif()

add_test(
	NAME MathTest
	COMMAND python
		${CMAKE_SOURCE_DIR}/tools/check_clang_tidy.py ${CMAKE_SOURCE_DIR}/math/tests/math_test.cpp liut_math-unqualified-math-functions tmp --
		-load=${MATH_DLL_PATH}
		-config={"Checks": "'-*,liut_math-unqualified-math-functions'"}
	WORKING_DIRECTORY ..
)
