#ifndef PARSER_H__TOSTITOS
#define PARSER_H__TOSTITOS

#include "lexer.h"

#include <memory>

namespace TosLang
{
    namespace FrontEnd
    {
        class ASTNode;
        class CompoundStmt;
        class Expr;
        class FunctionDecl;
        class IfStmt;
        class PrintStmt;
        class ReturnStmt;
        class ScanStmt;
        class SleepStmt;
        class VarDecl;
        class WhileStmt;
        
        /*
        * \class Parser
        * \brief Part of the TosLang compiler used to generate an AST
        */
        class Parser
        {
        public:
            explicit Parser() : mCurrentToken{ Lexer::Token::UNKNOWN } { }
            ~Parser() = default;

            /*
            * \fn               ParseProgram
            * \brief            Generate an AST from
            * \param filename   Name of a TosLang file
            * \return           Root node of the AST
            */
            std::unique_ptr<ASTNode> ParseProgram(const std::string& filename);
            
        private:	// Declarations
            /*
            * \fn       ParseProgramDecl
            * \brief    programdecl ::= decls
            * \return   A node representing a program
            */
            std::unique_ptr<ASTNode> ParseProgramDecl();

            /*
            * \fn       ParseFunctionDecl
            * \brief    functiondecl ::= 'fn' identifierexpr '(' ( vardecl, )* ')' '->' typeexpr compoundstmt
            * \return   A node representing a function declaration or definition
            */
            std::unique_ptr<FunctionDecl> ParseFunctionDecl();

            /*
            * \fn       ParseVarDecl
            * \brief    vardecl ::= 'var' identifierexpr ':' typeexpr ( '=' expr )? ';'
            * \return   A node representing a variable declaration with potentially an initializing expression
            */
            std::unique_ptr<VarDecl> ParseVarDecl();

		private:	// Expressions
			/*
			* \fn       ParseExpr
			* \brief    expr 
            *               ::= arrayexpr
            *               ::= binopexpr
            *               ::= booleanexpr
            *               ::= identifierexpr
            *               ::= indexedexpr
            *               ::= numberexpr
            *               ::= spawnexpr
            *               ::= stringexpr
			* \return   A node representing an expression
			*/
			std::unique_ptr<Expr> ParseExpr();

            /*
            * \fn           ParseArrayExpr
            * \brief        arrayexpr 
            *                   ::= '{' '}'
            *                   ::= '{' expr(',' expr)* '}'
            * \param lhs    The left hand side expression of the binary expression
            * \param op     The operation in the binary expression
            * \return       A node representing a binary expression
            */
            std::unique_ptr<Expr> ParseArrayExpr();

			/*
			* \fn           ParseBinaryOpExpr
			* \brief        binopexpr ::= expr OP expr
            * \param lhs    The left hand side expression of the binary expression
            * \param op     The operation in the binary expression
			* \return       A node representing a binary expression 
            */
			std::unique_ptr<Expr> ParseBinaryOpExpr(Lexer::Token operationToken, std::unique_ptr<Expr>&& lhs);

            /*
            * \fn                   ParseCallExpr
            * \brief                callexpr ::= identifierexpr '(' expr* ')'
            * \param fn             The function to be called
            * \param isSpawnedExpr  Is this a regular function call or one that'll spawn a thread?
            * \return               A node representing function call expression
            */
            std::unique_ptr<Expr> ParseCallExpr(std::unique_ptr<Expr>&& fn, const bool isSpawnedExpr);

        private:    // Statements
            /*
            * \fn           ParseCompoundStmt
            * \brief        compoundstmt ::= '{' stmt* '}'
            * \return       A node representing a compound statement i.e. an aggregation of statements
            */
            std::unique_ptr<CompoundStmt> ParseCompoundStmt();

            /*
            * \fn           ParseIfStmt
            * \brief        ifstmt ::= 'if' expr compoundstmt
            * \return       A node representing an if statement
            */
            std::unique_ptr<IfStmt> ParseIfStmt();

            /*
            * \fn           ParsePrintStmt
            * \brief        printstmt ::= 'print' expr
            * \return       A node representing a print statement
            */
            std::unique_ptr<PrintStmt> ParsePrintStmt();

            /*
            * \fn           ParseReturnStmt
            * \brief        'return' expr? ';'
            * \return       A node representing a return statement
            */
            std::unique_ptr<ReturnStmt> ParseReturnStmt();

            /*
            * \fn           ParseScanStmt
            * \brief        scanstmt ::= 'scan' identifierexpr
            * \return       A node representing a scan statement
            */
            std::unique_ptr<ScanStmt> ParseScanStmt();

            /*
            * \fn           ParseSleepStmt
            * \brief        sleepstmt ::= 'sleep' expr
            * \return       A node representing a sleep statement
            */
            std::unique_ptr<SleepStmt> ParseSleepStmt();

            /*
            * \fn           ParseWhileStmt
            * \brief        whilestmt ::= 'while' expr compoundstmt
            * \return       A node representing a while statement
            */
            std::unique_ptr<WhileStmt> ParseWhileStmt();
            
        private:    // Helpers
            /*
            * \fn                       ParseArrayType
            * \brief                    Parses an array type specification
            * \param[OUT]    arraySize  Size of the array
            * \param[IN/OUT] arrayType  Type of the array
            * \return                   Success
            */
            bool ParseArrayType(int& arraySize, Common::Type& arrayType);

        private:
            Lexer mLexer;                               /*!< Lexer used by the parser to acquire tokens */
            Lexer::Token mCurrentToken;                 /*!< Current token being treated by the parser */
        };
    }
}

#endif // PARSER_H__TOSTITOS
