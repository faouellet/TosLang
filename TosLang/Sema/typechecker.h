#ifndef TYPE_CHECKER_H__TOSLANG
#define TYPE_CHECKER_H__TOSLANG

#include "../Common/astvisitor.h"
#include "../Common/type.h"

#include <memory>
#include <stack>
#include <unordered_map>

namespace TosLang
{
    namespace FrontEnd
    {
        class BinaryOpExpr;
        class Expr;
        class FunctionDecl;
        class Symbol;
        class SymbolTable;

        /*
        * \class TypeChecker
        * \brief AST pass that verifies if no type error occurs when a variable or a function is used
        */
        class TypeChecker : public Common::ASTVisitor<TypeChecker>
        {
            friend class Common::ASTVisitor<TypeChecker>;

        public:
            TypeChecker();

        public:
            size_t Run(const std::unique_ptr<ASTNode>& root, const std::shared_ptr<SymbolTable>& symTab);
            
        private:
            bool CheckExprEvaluateToType(const Expr* expr, Common::Type type);

        protected:  // Declarations
            void HandleVarDecl();

        protected:  // Expressions
            void HandleArrayExpr();
            void HandleBooleanExpr();
            void HandleBinaryExpr();
            void HandleCallExpr();
            void HandleIdentifierExpr();
            void HandleIndexedExpr();
            void HandleNumberExpr();
            void HandleSpawnExpr();
            void HandleStringExpr();

        protected:  // Statements
            void HandleIfStmt();
            void HandleReturnStmt();
            void HandleSleepStmt();
            void HandleWhileStmt();

        private:
            using NodeTypeMap = std::unordered_map<const ASTNode*, Common::Type>;
            using OverloadMap = std::unordered_map<const ASTNode*, std::vector<const Symbol*>>;
            
        private:
            size_t mErrorCount;                         /*!< Number of errors found by the type checker */
            size_t mCurrentScopeID;                     /*!< Current scope identifier */
            const FunctionDecl* mCurrentFunc;           /*!< Current traversed function */
            std::deque<size_t> mCurrentScopesTraversed; /*!< Path from the current scope to the global scopes */
            std::shared_ptr<SymbolTable> mSymbolTable;  /*!< Symbol table to be used by the type checker */
            NodeTypeMap mNodeTypes;                     /*!< Type of the value produced by an AST node */
            OverloadMap mOverloadMap;                   /*!< Mapping between a function call and its overload set */
        };
    }
}

#endif // TYPE_CHECKER_H__TOSLANG
