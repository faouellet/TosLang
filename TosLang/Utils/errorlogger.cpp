#include "errorlogger.h"

#include "sourceloc.h"

#include <iostream>

using namespace TosLang::Utils;

std::unordered_map<ErrorLogger::ErrorType, std::string, ErrorLogger::ErrorTypeHash> ErrorLogger::mErrorMessages =
{

    // Array
    { ErrorType::ARRAY_EMPTY_EXPR,              "ERROR: Empty array expression" },
    { ErrorType::ARRAY_MISSING_COMMA,           "ERROR: Missing comma between two array elements" },
    { ErrorType::ARRAY_MISSING_NUMBER,          "ERROR: Missing array length specifier" },
    { ErrorType::ARRAY_MISSING_RIGHT_BRACKET,   "ERROR: Missing right bracket in array specification" },
    { ErrorType::ARRAY_MULTIPLE_TYPES,          "ERROR: Every expression in an array expression must be of the same type" },
    { ErrorType::ARRAY_NOT_A_NUMBER,            "ERROR: Array length specifier must be a number literal" },
    { ErrorType::ARRAY_UNEXPECTED_END,          "ERROR: Unexpected end of array expression" },
    { ErrorType::ARRAY_ZERO_LENGTH,             "ERROR: Array length must be greater than 0" },

    // Binary Expr
    { ErrorType::MISSING_RHS,                   "ERROR: Missing right hand side in binary expression" },
    { ErrorType::WRONG_OPERATION,               "ERROR: Not an acceptable binary operation" },
    { ErrorType::WRONG_USE_OPERATION,           "ERROR: Not an acceptable use of a binary operation" },
    
    // Call
    { ErrorType::CALL_MISSING_PAREN,            "CALL ERROR: Function call is missing a closing parenthesis" },
    { ErrorType::CALL_ARG_ERROR,                "CALL ERROR: Incorrect function call arguments" },
    { ErrorType::CALL_PARAM_TYPE_ERROR,         "CALL ERROR: No function matches these arguments types" },
    { ErrorType::CALL_RETURN_ERROR,             "CALL ERROR: No function matches the expected return type" },
    { ErrorType::CALL_NB_ARGS_ERROR,            "CALL ERROR: Trying to call a function with the wrong number of arguments" },
    

    // File
    { ErrorType::WRONG_FILE_TYPE,               "FILE ERROR: Wrong file type" },
    { ErrorType::ERROR_OPENING_FILE,            "FILE ERROR: Problem opening the specified file" },

    // Function
    { ErrorType::FN_INTERNAL,                   "FUNCTION ERROR: Internal functions are not allowed" },
    { ErrorType::FN_MISSING_ARROW,              "FUNCTION ERROR: Missing arrow to return type" },
    { ErrorType::FN_MISSING_TYPE,               "FUNCTION ERROR: Missing type from function declaration" },
    { ErrorType::FN_MISSING_IDENTIFIER,         "FUNCTION ERROR: The fn keyword should be followed by an identifier" },
    { ErrorType::FN_MISSING_LEFT_PAREN,         "FUNCTION ERROR: Missing left parenthesis in the function declaration" },
    { ErrorType::FN_MISSING_RIGHT_PAREN,        "FUNCTION ERROR: Missing right parenthesis in the function declaration" },
    { ErrorType::FN_MISSING_RETURN,             "FUNCTION ERROR: Missing return statement" },
    { ErrorType::FN_MISSING_RETURN_TYPE,        "FUNCTION ERROR: Missing return type" },
    { ErrorType::FN_REDEFINITION,               "FUNCTION ERROR: Trying to redefine an already defined function" },
    { ErrorType::FN_UNDECLARED,                 "FUNCTION ERROR: Trying to call an undeclared function" },

    // If
    { ErrorType::IF_MISSING_BODY,               "IF ERROR: Missing if body" },
    { ErrorType::IF_MISSING_COND,               "IF ERROR: Missing if condition" },

    // IO
    { ErrorType::PRINT_WRONG_INPUT_TYPE,        "PRINT ERROR: Cannot print given expression" },
    { ErrorType::SCAN_MISSING_INPUT_VAR,        "SCAN ERROR: Missing input variable" },
    { ErrorType::SCAN_WRONG_INPUT_TYPE,         "SCAN ERROR: Input variable is not an identfier" },

    // Literal
    { ErrorType::NEW_LINE_IN_LITERAL,           "LITERAL ERROR: Newline in string literal" },
    { ErrorType::MISSING_CLOSING_QUOTE,         "LITERAL ERROR: Missing closing quote" },
    { ErrorType::NUMBER_BAD_SUFFIX,             "LITERAL ERROR: Bad suffix on number" },

    // Misc
    { ErrorType::EXPECTED_DECL,                 "ERROR: Expected a declaration" },
    { ErrorType::MISSING_SEMI_COLON,            "ERROR: Expected a ;" },
    { ErrorType::UNCLOSED_ML_COMMENT,           "ERROR: Unclosed multiline comment" },

    // Param
    { ErrorType::PARAM_MISSING_COLON,           "PARAM ERROR: Missing colon between a parameter and its type" },
    { ErrorType::PARAM_MISSING_NAME,            "PARAM ERROR: Expected parameter name" },
    { ErrorType::PARAM_MISSING_TYPE,            "PARAM ERROR: Expected parameter type" },
    
    // Syntax
    { ErrorType::SYNTAX_MISSING_LBRACE,         "SYNTAX ERROR: Expected '{'" },
    { ErrorType::SYNTAX_MISSING_RBRACE,         "SYNTAX ERROR: Expected '}'" },

    // Type
    { ErrorType::WRONG_BIN_EXPR_TYPE,           "TYPE ERROR: Mismatch between binary expression operands type" },
    { ErrorType::WRONG_COND_EXPR_TYPE,          "TYPE ERROR: Conditional expression must evaluate to a boolean value" },
    { ErrorType::WRONG_EXPR_TYPE,               "TYPE ERROR: Trying to instantiate variable with an expression of the wrong type" },
    { ErrorType::WRONG_INIT_ARRAY_SCALAR,       "TYPE ERROR: Trying to instantiate an array variable with a scalar value" },
    { ErrorType::WRONG_INIT_SCALAR_ARRAY,       "TYPE ERROR: Trying to instantiate a scalar variable with an array expression" },
    { ErrorType::WRONG_LITERAL_TYPE,            "TYPE ERROR: Trying to instantiate variable with a literal of the wrong type" },
    { ErrorType::WRONG_RETURN_TYPE,             "TYPE ERROR: Returned value type doesn't match the function specified return type" },
    { ErrorType::WRONG_VARIABLE_TYPE,           "TYPE ERROR: Trying to initialize a variable with another variable of a different type" },

    // Var
    { ErrorType::PARAM_REDEFINITION,            "VAR ERROR: Trying to redefine an already defined function parameter" },
    { ErrorType::VAR_MISSING_TYPE,              "VAR ERROR: Missing type from variable declaration" },
    { ErrorType::VAR_MISSING_COLON,             "VAR ERROR: Missing : between a variable and its type" },
    { ErrorType::VAR_MISSING_IDENTIFIER,        "VAR ERROR: The var keyword should be followed by an identifier" },
    { ErrorType::VAR_REDEFINITION,              "VAR ERROR: Trying to redefine an already defined variable" },
    { ErrorType::VAR_UNDECLARED_IDENTIFIER,     "VAR ERROR: Trying to use an undeclared variable" },
    { ErrorType::VAR_VOID_TYPE,                 "VAR ERROR: Trying to create a variable with void type" },

    // While
    { ErrorType::WHILE_MISSING_BODY,            "WHILE ERROR: Missing while body" },
    { ErrorType::WHILE_MISSING_COND,            "WHILE ERROR: Missing while condition" },
};

/*
* \fn           PrintError
* \param eType  Type of error to log
* \brief        Logs the error of the type eType to the stderr
*/
void ErrorLogger::PrintError(ErrorType eType)
{
    std::cerr << mErrorMessages[eType] << std::endl;
}

/*
* \fn           PrintErrorAtLocation
* \param eType  Type of error to log
* \param srcLoc Location in the source code where the error happened
* \brief        Logs the error of the type eType with source location information to the stderr
*/
void ErrorLogger::PrintErrorAtLocation(ErrorType eType, const SourceLocation& srcLoc)
{
    std::cerr << mErrorMessages[eType] << " at line " << srcLoc.GetCurrentLine() << ", column " << srcLoc.GetCurrentColumn() << std::endl;
}
