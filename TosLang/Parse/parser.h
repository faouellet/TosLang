#ifndef PARSER_H__TOSLANG
#define PARSER_H__TOSLANG

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

            std::unique_ptr<ASTNode> ParseProgram(const std::string& filename);
            
        private:	// Declarations
            std::unique_ptr<ASTNode> ParseProgramDecl();
            std::unique_ptr<FunctionDecl> ParseFunctionDecl();
            std::unique_ptr<VarDecl> ParseVarDecl();

		private:	// Expressions
			std::unique_ptr<Expr> ParseExpr();
            std::unique_ptr<Expr> ParseArrayExpr();
			std::unique_ptr<Expr> ParseBinaryOpExpr(Lexer::Token operationToken, std::unique_ptr<Expr>&& lhs);
            std::unique_ptr<Expr> ParseCallExpr(std::unique_ptr<Expr>&& fn, const bool isSpawnedExpr);

        private:    // Statements
            std::unique_ptr<CompoundStmt> ParseCompoundStmt();
            std::unique_ptr<IfStmt> ParseIfStmt();
            std::unique_ptr<PrintStmt> ParsePrintStmt();
            std::unique_ptr<ReturnStmt> ParseReturnStmt();
            std::unique_ptr<ScanStmt> ParseScanStmt();
            std::unique_ptr<SleepStmt> ParseSleepStmt();
            std::unique_ptr<WhileStmt> ParseWhileStmt();
            
        private:    // Helpers
            bool ParseArrayType(int& arraySize, Common::Type& arrayType);

        private:
            Lexer mLexer;               /*!< Lexer used by the parser to acquire tokens */
            Lexer::Token mCurrentToken; /*!< Current token being treated by the parser */
        };
    }
}

#endif // PARSER_H__TOSLANG
