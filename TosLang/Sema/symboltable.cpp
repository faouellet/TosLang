#include "symboltable.h"

#include "../AST/declarations.h"

#include <algorithm>
#include <iterator>
#include <sstream>

using namespace TosLang::FrontEnd;
using namespace TosLang::Common;

bool SymbolTable::AddSymbol(const ASTNode* node, Symbol&& sym)
{
    if (node == nullptr)
        return false;

    const ASTNode::NodeKind kind = node->GetKind();

    assert(kind == ASTNode::NodeKind::FUNCTION_DECL
           || kind == ASTNode::NodeKind::VAR_DECL);

    auto symIt = std::find_if(mTable.begin(), mTable.end(), 
                              [&sym](const std::pair<const ASTNode*, Symbol>& nodeSym)
                              {
                                  const Symbol& symbol = nodeSym.second;

                                  if (symbol.IsFunction() && sym.IsFunction())
                                  {
                                      // Check for every aspects of a function
                                      const std::vector<Common::Type>& candidateParamTypes = symbol.GetFunctionParamTypes();
                                      const std::vector<Common::Type>& expectedParamTypes = sym.GetFunctionParamTypes();

                                      return candidateParamTypes.size() == expectedParamTypes.size()
                                          && candidateParamTypes == expectedParamTypes
                                          && symbol.GetFunctionReturnType() == sym.GetFunctionReturnType()
                                          && symbol.GetName() == sym.GetName();
                                  }
                                  else if (!symbol.IsFunction() && !sym.IsFunction())
                                  {
                                      // Check only for the scope and the name to disallow declaring 
                                      // the same variable with another type
                                      return symbol.GetScopeID() == sym.GetScopeID()
                                          && symbol.GetName() == sym.GetName();
                                  }
                                  else
                                  {
                                      return false;
                                  }
                              });

    // Symbol was already defined
    if (symIt != mTable.end())
        return false;

    mTable[node] = sym;

    return true;
}

bool SymbolTable::AddVariableUse(const IdentifierExpr* iExpr, const std::deque<size_t>& scopePath)
{
    for (const auto& scopeID : scopePath)
    {
        auto varIt = std::find_if(mTable.begin(), mTable.end(), 
                     [&scopeID, &iExpr](const std::pair<const ASTNode*, Symbol>& nodeSym) 
                     {
                         return nodeSym.second.GetScopeID() == scopeID
                             && nodeSym.second.GetName() == iExpr->GetName();
                     });

        if (varIt != mTable.end())
        {
            mUseDefs[iExpr] = varIt->first;
            return true;
        }
    }

    return false;
}

bool SymbolTable::AddFunctionUse(const CallExpr* cExpr, const Symbol& fnSym)
{
    auto fnIt = std::find_if(mTable.begin(), mTable.end(),
                            [&fnSym, &cExpr](const std::pair<const ASTNode*, Symbol>& nodeSym)
                            {
                                return nodeSym.second == fnSym;
                            });

    if (fnIt != mTable.end())
    {
        mUseDefs[cExpr] = fnIt->first;
        return true;
    }

    return false;
}


std::pair<bool, const Symbol*> SymbolTable::TryGetSymbol(const ASTNode* node) const
{
    if (node == nullptr)
        return { false, nullptr };

    const ASTNode* nodeForLookup = node;
    ASTNode::NodeKind nodeKind = nodeForLookup->GetKind();

    // An identifier or a call is a use. Since the symbol table only contains information
    // about definitions, we need to find the corresponding definition to this use
    if (( nodeKind == ASTNode::NodeKind::IDENTIFIER_EXPR)
        || (nodeKind == ASTNode::NodeKind::CALL_EXPR))
    {
        auto udIt = mUseDefs.find(node);
        if (udIt != mUseDefs.end())
            nodeForLookup = udIt->second;
        else
            return { false, nullptr };
    }
    
    nodeKind = nodeForLookup->GetKind();

    if ((nodeKind == ASTNode::NodeKind::FUNCTION_DECL)
        || (nodeKind == ASTNode::NodeKind::VAR_DECL))
    {
        auto symIt = mTable.find(nodeForLookup);
        if (symIt != mTable.end())
        {
            return { true, &symIt->second };
        }
    }
    
    // Unhandled node type
    return { false, nullptr };
}

std::vector<const Symbol*> SymbolTable::GetOverloadCandidates(const std::string& fnName) const
{
    std::vector<const Symbol*> overloadCandidates;

    for (const auto& nodeSym : mTable)
    {
        if ((nodeSym.first->GetKind() == ASTNode::NodeKind::FUNCTION_DECL)
            && (nodeSym.second.GetName() == fnName))
        {
            overloadCandidates.push_back(&nodeSym.second);
        }
    }

    return overloadCandidates;
}

const ASTNode* SymbolTable::GetFunctionDecl(const Symbol& fnSym) const
{
    auto fnIt = std::find_if(mTable.begin(), mTable.end(),
                             [&fnSym](const std::pair<const ASTNode*, Symbol>& nodeSym)
                             {
                                 return nodeSym.second == fnSym;
                             });

    if (fnIt != mTable.end())
        return fnIt->first;
    else
        return nullptr;
}

const ASTNode* SymbolTable::GetFunctionDecl(const ASTNode* callExpr) const
{
    assert(callExpr->GetKind() == ASTNode::NodeKind::CALL_EXPR);
    return mUseDefs.at(callExpr);
}

const ASTNode* SymbolTable::GetVarDecl(const ASTNode* identExpr) const
{
    assert(identExpr->GetKind() == ASTNode::NodeKind::IDENTIFIER_EXPR);
    return mUseDefs.at(identExpr);
}

bool SymbolTable::IsFunctionSymbolValid(const Symbol& fnSym) const
{
    auto fnIt = std::find_if(mTable.begin(), mTable.end(), 
                             [&fnSym](const std::pair<const ASTNode*, Symbol> nodeSym)
                             {
                                 return nodeSym.first->GetKind() == ASTNode::NodeKind::FUNCTION_DECL
                                     && nodeSym.second == fnSym;
                             });

    return fnIt != mTable.end();
}

bool SymbolTable::IsFunctionNameValid(const std::string& fnName) const
{
    auto fnIt = std::find_if(mTable.begin(), mTable.end(),
                             [&fnName](const std::pair<const ASTNode*, Symbol> nodeSym)
                             {
                                 return nodeSym.first->GetKind() == ASTNode::NodeKind::FUNCTION_DECL
                                     && nodeSym.second.GetName() == fnName;
                             });

    return fnIt != mTable.end();
}

bool SymbolTable::IsVariableSymbolValid(const Symbol & varSym) const
{
    auto fnIt = std::find_if(mTable.begin(), mTable.end(),
                             [&varSym](const std::pair<const ASTNode*, Symbol> nodeSym)
                             {
                                 return nodeSym.first->GetKind() == ASTNode::NodeKind::VAR_DECL
                                     && nodeSym.second == varSym;
                             });

    return fnIt != mTable.end();
}

bool SymbolTable::IsGlobalVariable(const ASTNode* node) const
{
    assert(node != nullptr);

    ASTNode::NodeKind nodeKind = node->GetKind();
    assert((nodeKind == ASTNode::NodeKind::IDENTIFIER_EXPR)
        || (nodeKind == ASTNode::NodeKind::VAR_DECL));

    const ASTNode* nodeForLookup = node;

    if (nodeKind == ASTNode::NodeKind::IDENTIFIER_EXPR)
    {
        auto udIt = mUseDefs.find(node);
        assert(udIt != mUseDefs.end());
        nodeForLookup = udIt->second;
    }

    auto symIt = mTable.find(nodeForLookup);
    assert(symIt != mTable.end());

    return symIt->second.GetScopeID() == 0;
}

