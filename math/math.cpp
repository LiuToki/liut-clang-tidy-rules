//===--- UnqualifiedMathFunctionsCheck.cpp - clang-tidy -----------------===//
//
// This file defines a clang-tidy check that detects unqualified calls to 
// sin, cos, and tan and suggests using the std::-qualified versions instead.
//
//===----------------------------------------------------------------------===//

#pragma warning(push)
#pragma warning(disable: 4291)
#pragma warning(disable: 4819)
#include "clang-tidy//ClangTidyCheck.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#pragma warning(pop)

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace my_checks {

class UnqualifiedMathFunctionsCheck : public ClangTidyCheck {
public:
  UnqualifiedMathFunctionsCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}

  void registerMatchers(MatchFinder *Finder) override {
    // マッチャーで、名前が "sin", "cos", "tan" の関数呼び出しで、 
    // 呼び出しが std 名前空間以外の関数を検出する。
    Finder->addMatcher(
      callExpr(
        callee(functionDecl(
          hasAnyName("sin", "cos", "tan"),
          // 関数が所属する宣言コンテキストが std でない場合
          unless(hasDeclContext(namespaceDecl(hasName("std"))))
        )).bind("unqualifiedCall")
      ),
      this
    );
  }

  void check(const MatchFinder::MatchResult &Result) override {
    const auto *Call = Result.Nodes.getNodeAs<CallExpr>("unqualifiedCall");
    if (!Call)
      return;
    
    // 警告メッセージ：対象関数名を利用して std::xxx を使うよう促す
    diag(Call->getExprLoc(),
         "unqualified call to '%0'; consider using 'std::%0' instead")
         << Call->getDirectCallee()->getName();
  }
};

} // namespace my_checks

// このモジュールを clang-tidy に登録するための仕組み
namespace {
class UnqualifiedMathFunctionsModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &Factories) override {
    Factories.registerCheck<my_checks::UnqualifiedMathFunctionsCheck>(
        "my-checks-unqualified-math-functions");
  }
};
} // namespace

// モジュールの登録（これにより clang-tidy がこのチェックを認識する）
static ClangTidyModuleRegistry::Add<UnqualifiedMathFunctionsModule>
    X("my-checks-module", "Adds checks for unqualified math functions (sin, cos, tan).");

// このアンカー変数はリンカによりこのモジュールが確実にリンクされるために使います。
volatile int UnqualifiedMathFunctionsModuleAnchorSource = 0;
