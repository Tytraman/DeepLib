#include "core.hpp"
#include "memory/memory.hpp"
#include "memory/ref_counted.hpp"

class test_ref_counted : public deep::ref_counted
{
};

int main(int argc, char *argv[])
{
    deep::ctx context;

    if (!deep::core::core::create_context(context))
    {
        return 1;
    }

    deep::ref<test_ref_counted> ref_test_1 = deep::mem::alloc_type<test_ref_counted>();

    if (ref_test_1->get_ref_count() != 1)
    {
        return 1;
    }

    deep::ref<test_ref_counted> ref_test_2 = ref_test_1;

    if (ref_test_1->get_ref_count() != 2)
    {
        return 1;
    }

    {
        deep::ref<test_ref_counted> ref_test_3 = ref_test_1;

        if (ref_test_1->get_ref_count() != 3)
        {
            return 1;
        }
    }

    if (ref_test_2->get_ref_count() != 2)
    {
        return 1;
    }

    if (!deep::core::core::destroy_context(context))
    {
        return 1;
    }

    return 0;
}
