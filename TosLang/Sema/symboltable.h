#ifndef SYMBOL_TABLE_H__TOSTITOS
#define SYMBOL_TABLE_H__TOSTITOS

#include "symbol.h"

#include <deque>
#include <unordered_map>

namespace TosLang
{
    namespace FrontEnd
    {
        class ASTNode;
        class CallExpr;
        class IdentifierExpr;
        class VarDecl;

        /*
        * \class SymbolTable
        * \brief Manages the symbols produced by the compiler. 
        *        Concretly, this is where the symbols produced by the symbol collection pass are put. 
        *        They are then later queried by the type checker and the instruction selector.
        */
        class SymbolTable
        {
        public:
            bool AddSymbol(const ASTNode* node, Symbol&& sym);
            bool AddVariableUse(const IdentifierExpr* iExpr, const std::deque<size_t>& scopePath);
            bool AddFunctionUse(const CallExpr* cExpr, const Symbol& fnSym);

            /*
            * \fn       Clear
            * \brief    Clears all the internal structures maintained by the symbol table
            */
            void Clear() { mTable.clear(); }

            std::pair<bool, const Symbol*> TryGetSymbol(const ASTNode* node) const;
            std::vector<const Symbol*> GetOverloadCandidates(const std::string& fnName) const;
            const ASTNode* GetFunctionDecl(const Symbol& fnSym) const;
            const ASTNode* GetFunctionDecl(const ASTNode* identExpr) const;            
            const ASTNode* GetVarDecl(const ASTNode* identExpr) const;
            bool IsFunctionNameValid(const std::string& fnName) const;
            bool IsFunctionSymbolValid(const Symbol& fnSym) const;
            bool IsVariableSymbolValid(const Symbol& varSym) const;
            bool IsGlobalVariable(const ASTNode* var) const;
            
        private:
            using SymTable = std::unordered_map<const ASTNode*, Symbol>;
            using UseDefMap = std::unordered_map<const ASTNode*, const ASTNode*>;
            
        private:
            SymTable mTable;    /*!< Table containing all symbol defined in the program */
            UseDefMap mUseDefs; /*!< Mapping between the uses and the definition of a variable */
        };
    }
}

#endif // SYMBOL_TABLE_H__TOSTITOS
