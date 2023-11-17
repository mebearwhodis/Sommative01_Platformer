#include "Interactive.h"

Interactive::Interactive()
= default;

Interactive::Interactive(const InteractiveType type, const bool temporary, const bool deadly, const bool taken)
{
    interactive_type_ = type;
    temporary_ = temporary;
    deadly_ = deadly;
    taken_ = taken;
}


