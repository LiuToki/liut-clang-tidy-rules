#include <cmath>

// unqualified な sin の呼び出し（警告が期待される）
// CHECK-MESSAGES: :[[@LINE+1]]: warning: unqualified call to 'sin'; consider using 'std::sin' instead [liut_math-unqualified-math-functions]
double test_sin(double x) {
  return sin(x);
}

// unqualified な cos と tan の呼び出し（いずれも警告が期待される）
double test_cos_tan(double x) {
  // CHECK-MESSAGES: :[[@LINE+1]]: warning: unqualified call to 'cos'; consider using 'std::cos' instead [liut_math-unqualified-math-functions]
  double a = cos(x);
  // CHECK-MESSAGES: :[[@LINE+1]]: warning: unqualified call to 'tan'; consider using 'std::tan' instead [liut_math-unqualified-math-functions]
  double b = tan(x);
  return a + b;
}

// std:: を付与した呼び出し（警告は発生しないことが期待される）
double test_std_functions(double x) {
  return std::sin(x) + std::cos(x) + std::tan(x);
}

int main() {
  double x = 0.5;
  double r1 = test_sin(x);
  double r2 = test_cos_tan(x);
  double r3 = test_std_functions(x);
  return static_cast<int>(r1 + r2 + r3);
}
