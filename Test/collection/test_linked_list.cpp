#include "DeepLib/lib.hpp"
#include "DeepLib/collection/linked_list.hpp"

class test_linked_list
{
  public:
    test_linked_list(deep::int32 value) noexcept;

    deep::int32 get_value() const noexcept;

  private:
    deep::int32 m_value;
};

test_linked_list::test_linked_list(deep::int32 value) noexcept
        : m_value(value)
{
}

deep::int32 test_linked_list::get_value() const noexcept
{
    return m_value;
}

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::linked_list<test_linked_list> test_list = deep::linked_list<test_linked_list>(context);

    if (!test_list.add(6))
    {
        return 10;
    }

    if (!test_list.add(74))
    {
        return 11;
    }

    if (!test_list.add(128))
    {
        return 12;
    }

    test_linked_list *tll_0 = test_list[0];
    test_linked_list *tll_1 = test_list[1];
    test_linked_list *tll_2 = test_list[2];
    test_linked_list *tll_3 = test_list[3];

    if (tll_0 == nullptr)
    {
        return 20;
    }

    if (tll_1 == nullptr)
    {
        return 21;
    }

    if (tll_2 == nullptr)
    {
        return 22;
    }

    if (tll_0->get_value() != 6)
    {
        return 23;
    }

    if (tll_1->get_value() != 74)
    {
        return 24;
    }

    if (tll_2->get_value() != 128)
    {
        return 25;
    }

    if (tll_3 != nullptr)
    {
        return 26;
    }

    test_linked_list *tll = test_list.get_last();
    if (tll == nullptr)
    {
        return 30;
    }

    if (tll->get_value() != 128)
    {
        return 31;
    }

    if (test_list.count() != 3)
    {
        return 32;
    }

    deep::int32 counter;

    for (counter = 0; counter < 10; ++counter)
    {
        if (!test_list.add(counter))
        {
            return 40;
        }
    }

    if (test_list.count() != 13)
    {
        return 41;
    }

    tll_3 = test_list[3];
    if (tll_3 == nullptr)
    {
        return 42;
    }
    if (tll_3->get_value() != 0)
    {
        return 43;
    }

    if (!test_list.remove(3))
    {
        return 44;
    }

    tll_3 = test_list[3];
    if (tll_3 == nullptr)
    {
        return 45;
    }
    if (tll_3->get_value() != 1)
    {
        return 46;
    }

    if (test_list.count() != 12)
    {
        return 47;
    }

    if (!test_list.remove(0))
    {
        return 48;
    }

    tll_0 = test_list[0];
    if (tll_0 == nullptr)
    {
        return 49;
    }
    if (tll_0->get_value() != 74)
    {
        return 50;
    }

    deep::linked_list<test_linked_list> test_swap = deep::linked_list<test_linked_list>(context);

    if (!test_swap.add(31)) // [0]
    {
        return 51;
    }
    if (!test_swap.add(41)) // [1]
    {
        return 52;
    }
    if (!test_swap.add(51)) // [2]
    {
        return 53;
    }
    if (!test_swap.add(61)) // [3]
    {
        return 54;
    }

    tll_1 = test_swap[1];
    tll_3 = test_swap[3];

    if (tll_1 == nullptr || tll_1->get_value() != 41)
    {
        return 55;
    }
    if (tll_3 == nullptr || tll_3->get_value() != 61)
    {
        return 56;
    }

    if (!test_swap.swap(1, 3))
    {
        return 60;
    }

    tll_1 = test_swap[1];
    tll_3 = test_swap[3];

    if (tll_1 == nullptr || tll_1->get_value() != 61)
    {
        return 61;
    }
    if (tll_3 == nullptr || tll_3->get_value() != 41)
    {
        return 62;
    }

    if (!test_swap.swap(0, 3))
    {
        return 63;
    }

    tll_0 = test_swap[0];
    tll_3 = test_swap[3];

    if (tll_0 == nullptr || tll_0->get_value() != 41)
    {
        return 64;
    }
    if (tll_3 == nullptr || tll_3->get_value() != 31)
    {
        return 65;
    }

    return 0;
}
