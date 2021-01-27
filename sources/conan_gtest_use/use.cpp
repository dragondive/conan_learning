#include "use.h"

std::string use()
{
    return std::string("use: ") + get_hello() + " " + std::to_string(get_42());
}
    
