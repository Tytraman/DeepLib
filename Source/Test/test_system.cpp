#include "core.hpp"
#include "system.hpp"

int main(int argc, char *argv[])
{
    if (deep::core::get_current_system() == deep::system::Linux)
    {
        return 0;
    }

    return 1;
}
