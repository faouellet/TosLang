#ifndef OPCODE_H__TOSTITOS
#define OPCODE_H__TOSTITOS

namespace TosLang
{
    namespace Common
    {
        /**
        * \enum  Operation
        * \brief Operations available in TosLang
        */
        enum class Operation : unsigned int
        {
            ASSIGNMENT,
            AND_BOOL,
            AND_INT,
            DIVIDE,
            EQUAL,
            GREATER_THAN,
            LEFT_SHIFT,
            LESS_THAN,
            MINUS,
            MODULO,
            MULT,
            NOT,
            OR_BOOL,
            OR_INT,
            PLUS,
            RIGHT_SHIFT,
            UNKNOWN_OP
        };
    }
}

#endif // OPCODE_H__TOSTITOS