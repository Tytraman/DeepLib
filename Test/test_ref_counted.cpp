#include "DeepLib/lib.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/memory/ref_counted.hpp"

class test_ref_counted : public deep::ref_counted
{
  private:
    deep::uint32 m_value;
};

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::ref<test_ref_counted> ref_test_1 = deep::ref<test_ref_counted>(context.get(), deep::mem::alloc_type<test_ref_counted>(context.get()));

    if (ref_test_1->get_ref_count() != 1)
    {
        return 10;
    }

    deep::ref<test_ref_counted> ref_test_2 = ref_test_1;

    if (ref_test_1->get_ref_count() != 2)
    {
        return 11;
    }

    {
        deep::ref<test_ref_counted> ref_test_3 = ref_test_1;

        if (ref_test_1->get_ref_count() != 3)
        {
            return 12;
        }
    }

    if (ref_test_2->get_ref_count() != 2)
    {
        return 13;
    }

    return 0;
}
