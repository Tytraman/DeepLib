#include "DeepLib/lib.hpp"
#include "DeepLib/maths/vec.hpp"
#include "DeepLib/maths/mat.hpp"

template struct deep::mat4x4<float>;

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::fmat4 translation = deep::fmat4();
    translation             = deep::fmat4::translate(translation, deep::fvec3(3.0f, 4.0f, 5.0f));

    deep::string output = translation.to_string(context);

    context->out() << "Translation:\r\n"
                   << *output << "\r\n";

    deep::fmat4 fov_perspective = deep::fmat4();
    fov_perspective             = deep::fmat4::d3d_perspective_fov_lh(90.0f, 1920.0f / 1080.0f, 1.0f, 1000.0f);

    output = fov_perspective.to_string(context);

    context->out() << "fov perspective:\r\n"
                   << *output << "\r\n";

    deep::fvec3 location = deep::fvec3(5.0f, 0.0f, 0.0f);
    deep::fvec3 target   = deep::fvec3(5.0f, 2.0f, 1.0f);
    deep::fvec3 up       = deep::fvec3(0.0f, 1.0f, 0.0f);
    deep::fmat4 look_at  = deep::fmat4::d3d_look_at_lh(location, target, up);

    output = look_at.to_string(context);

    context->out() << "look at:\r\n"
                   << *output << "\r\n";

    return 0;
}
