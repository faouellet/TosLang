#include "sourceloc.h"

using namespace TosLang::Utils;

/*
* \fn       Init
* \brief    Initializes the SourceLocation to a valid state representing the start of a file
*/
void SourceLocation::Init()
{
    mCurrentColumn = 1;
    mCurrentLine = 1;
}

/*
* \fn               Advance
* \brief            Advances the SourceLocation to in the source file
* \param nextLine   Will advancing change the current line?
*/
void SourceLocation::Advance(bool nextLine)
{
    if (nextLine)
    {
        ++mCurrentLine;
        mCurrentColumn = 1;
    }
    else
    {
        ++mCurrentColumn;
    }
}
