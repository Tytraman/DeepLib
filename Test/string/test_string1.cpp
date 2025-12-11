#include "DeepLib/lib.hpp"
#include "DeepLib/string/string.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::string str = deep::string(context, DEEP_STRING("Hello "));

    if (!str.is_valid())
    {
        return 10;
    }

    if (str.get_length() != 6)
    {
        return 11;
    }

    str += DEEP_STRING("wérld");

    if (str.get_length() != 11)
    {
        return 12;
    }

    context->out() << *str << DEEP_STRING("\n");

    return 0;
}
