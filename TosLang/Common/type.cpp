#include "type.h"

#include <cassert>
#include <map>

using namespace TosLang::Common;

Type TosLang::Common::GetArrayVersion(const Type type)
{
    static std::map<Type, Type> tyToArrayTy{
        { Type::BOOL, Type::BOOL_ARRAY },
        { Type::NUMBER, Type::NUMBER_ARRAY },
        { Type::STRING, Type::STRING_ARRAY }
    };

    assert((type == Type::BOOL) || (type == Type::NUMBER) || (type == Type::STRING));

    return tyToArrayTy[type];
}
