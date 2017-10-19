#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#else
#ifndef _WIN32
#   define BOOST_TEST_MODULE ScopeCheckerVarTests
#endif
#endif

#include <boost/test/unit_test.hpp>

#include "toslang_sema_fixture.h"

BOOST_FIXTURE_TEST_SUITE( SemaTestSuite, TosLangSemaFixture )

//////////////////// CORRECT USE CASES ////////////////////

BOOST_AUTO_TEST_CASE( BasicCallScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/call/call_one_arg_var.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

BOOST_AUTO_TEST_CASE( CallChoiceScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/call/call_multiple_choices.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

//////////////////// ERROR USE CASES ////////////////////

BOOST_AUTO_TEST_CASE( UndeclaredFunctionCallScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/call/call_undeclared.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "FUNCTION ERROR: Trying to call an undeclared function at line 3, column 26");
}

BOOST_AUTO_TEST_SUITE_END()