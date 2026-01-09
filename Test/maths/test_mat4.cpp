#include "DeepLib/lib.hpp"
#include "DeepLib/maths/mat.hpp"

template struct deep::mat4x4<float>;

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    return 0;
}
