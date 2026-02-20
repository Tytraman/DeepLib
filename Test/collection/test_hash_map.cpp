#include "DeepLib/lib.hpp"
#include "DeepLib/collection/hash_map.hpp"

class test_object : public deep::object
{
  public:
    test_object(const deep::ref<deep::ctx> &context, deep::uint32 value) noexcept;

    deep::uint32 get_value() const noexcept;

  private:
    deep::uint32 m_value;

  public:
    friend deep::memory_manager;
};

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    constexpr const char *key1 = DEEP_STRING("super_key1");
    constexpr const char *key2 = DEEP_STRING("super_key2");
    constexpr const char *key3 = DEEP_STRING("super_key3");
    constexpr const char *key4 = DEEP_STRING("super_key4");

    deep::hash_map<deep::uint16> map(context.get());

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

    test_object *tobj = deep::mem::alloc_type<test_object>(context.get(), context, 52);
    if (tobj == nullptr)
    {
        return 100;
    }

    deep::ref<test_object> rtobj = deep::ref<test_object>(context, tobj);

    context->set_object("rtobj", rtobj);

    deep::ref<test_object> grtobj = context->get_object<test_object>("rtobj");
    if (!grtobj.is_valid())
    {
        return 101;
    }

    if (grtobj->get_value() != 52)
    {
        return 102;
    }

    return 0;
}

test_object::test_object(const deep::ref<deep::ctx> &context, deep::uint32 value) noexcept
        : deep::object(context),
          m_value(value)
{
}

deep::uint32 test_object::get_value() const noexcept
{
    return m_value;
}
