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

BOOST_AUTO_TEST_CASE( GlobalVarUsedInGlobalScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/var/var_init_identifier.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

BOOST_AUTO_TEST_CASE( GlobalVarUsedInLocalScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/var/var_init_identifier_from_global.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

BOOST_AUTO_TEST_CASE( LocalVarUsedInLocalScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/var/var_init_identifier_local.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 0);
}

//////////////////// ERROR USE CASES ////////////////////

BOOST_AUTO_TEST_CASE( UneclaredGlobalVarUsedInGlobalScopeCheck )
{

    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/var/var_init_identifier_undeclared.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "VAR ERROR: Trying to use an undeclared variable at line 1, column 24");
}

BOOST_AUTO_TEST_CASE( UndeclaredVarUsedInLocalScopeCheck )
{
    auto symbolTable = std::make_shared<TosLang::FrontEnd::SymbolTable>();
    size_t errorCount = GetProgramSymbolTable("../asts/var/var_init_identifier_local_undeclared.ast", symbolTable);
    BOOST_REQUIRE_EQUAL(errorCount, 1);

    // Check if the correct error message got printed
    std::vector<std::string> messages{ GetErrorMessages() };
    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_REQUIRE_EQUAL(messages[0], "VAR ERROR: Trying to use an undeclared variable at line 3, column 25");
}

BOOST_AUTO_TEST_SUITE_END()