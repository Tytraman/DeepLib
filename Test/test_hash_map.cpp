#include "DeepLib/lib.hpp"
#include "DeepLib/collection/hash_map.hpp"

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    constexpr const char *key1 = DEEP_STRING("super_key1");
    constexpr const char *key2 = DEEP_STRING("super_key2");
    constexpr const char *key3 = DEEP_STRING("super_key3");
    constexpr const char *key4 = DEEP_STRING("super_key4");

    deep::hash_map<deep::uint16> map(context);

    if (map.insert(key1, 150) == nullptr)
    {
        return 2;
    }

    if (map.insert(key2, 300) == nullptr)
    {
        return 3;
    }

    if (map.insert(key3, 555) == nullptr)
    {
        return 4;
    }

    if (map.insert(key4, 9876) == nullptr)
    {
        return 5;
    }

    deep::hash_entry<deep::uint16> *entry = map[key1];
    if (entry == nullptr)
    {
        return 6;
    }
    if (entry->value != 150)
    {
        return 7;
    }

    entry = map[key2];
    if (entry == nullptr)
    {
        return 8;
    }
    if (entry->value != 300)
    {
        return 9;
    }

    entry = map[key3];
    if (entry == nullptr)
    {
        return 10;
    }
    if (entry->value != 555)
    {
        return 11;
    }

    entry = map[key4];
    if (entry == nullptr)
    {
        return 12;
    }
    if (entry->value != 9876)
    {
        return 13;
    }

    if (map.get_number_of_elements() != 4)
    {
        return 14;
    }

    if (!map.remove(key1))
    {
        return 15;
    }

    entry = map[key1];
    if (entry != nullptr)
    {
        return 16;
    }

    if (map.get_number_of_elements() != 3)
    {
        return 17;
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
