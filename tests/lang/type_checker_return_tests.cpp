#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#else
#ifndef _WIN32
#   define BOOST_TEST_MODULE TypeCheckerReturnTests
#endif
#endif

#include <boost/test/unit_test.hpp>

#include "toslang_sema_fixture.h"

BOOST_FIXTURE_TEST_SUITE( SemaTestSuite, TosLangSemaFixture )

//////////////////// CORRECT USE CASES ////////////////////

BOOST_AUTO_TEST_CASE( ReturnBinaryExprTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/fn_def_multi_args.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

BOOST_AUTO_TEST_CASE( ReturnLiteralTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/fn_def_zero_arg.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

BOOST_AUTO_TEST_CASE( ReturnVariableTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/fn_def_one_arg.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

BOOST_AUTO_TEST_CASE( ReturnVoidTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/fn_def_void.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

//////////////////// ERROR USE CASES ////////////////////

BOOST_AUTO_TEST_CASE( BadReturnBinOpTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/bad_fn_return_bin_op.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "TYPE ERROR: Returned value type doesn't match the function specified return type at line 2, column 10");
}

BOOST_AUTO_TEST_CASE( BadReturnLiteralTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/bad_fn_return_literal.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "TYPE ERROR: Returned value type doesn't match the function specified return type at line 2, column 10");
}

BOOST_AUTO_TEST_CASE( BadReturnVoidTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/bad_fn_return_void.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "TYPE ERROR: Returned value type doesn't match the function specified return type at line 2, column 10");
}

BOOST_AUTO_TEST_CASE( BadReturnVariableTypeCheck )
{
    size_t errorCount = GetTypeErrors("../asts/function/bad_fn_return_variable.ast");
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "TYPE ERROR: Returned value type doesn't match the function specified return type at line 2, column 10");
}

BOOST_AUTO_TEST_SUITE_END()