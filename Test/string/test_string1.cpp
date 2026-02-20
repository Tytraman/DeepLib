#include "DeepLib/lib.hpp"
#include "DeepLib/string/string.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::string str = deep::string(context, DEEP_TEXT_UTF8("Hello "));

    if (!str.is_valid())
    {
        return 10;
    }

    if (str.get_length() != 6)
    {
        return 11;
    }

    str += DEEP_TEXT_UTF8("wérld");

    // Si la chaîne ne fait pas précisemment 11 caractères c'est qu'il y a un problème dans l'encodage.
    if (str.get_length() != 11)
    {
        return 12;
    }

    context->out() << *str << DEEP_TEXT_UTF8("\n");

    return 0;
}
