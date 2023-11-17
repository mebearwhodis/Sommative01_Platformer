#include "Interactive.h"

#include "Texture.h"

Interactive::Interactive()
= default;

Interactive::Interactive(const InteractiveType type, const bool temporary, const bool deadly)
{
    interactive_type_ = type;
    temporary_ = temporary;
    deadly_ = deadly;
    taken_ = false;
}


