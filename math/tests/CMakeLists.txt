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
add_test(
	NAME MathTest
	COMMAND python ${CMAKE_SOURCE_DIR}/test/check_clang_tidy.py ${CMAKE_SOURCE_DIR}/test/math.cpp readability-awesome-function-names tmp --
	-load=${CMAKE_BINARY_DIR}/libMath_${LLVM_VERSION_MAJOR}.so
	WORKING_DIRECTORY ..
)
