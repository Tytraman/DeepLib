#include "DeepLib/lib.hpp"
#include "DeepLib/string/string.hpp"

#include <stdio.h>

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    const char str1[] = DEEP_TEXT_UTF8("Hello World");
    const char str2[] = DEEP_TEXT_UTF8("Hello World");
    const char str3[] = DEEP_TEXT_UTF8("Hello Worlg");
    const char str4[] = DEEP_TEXT_UTF8("Hello World!");

    deep::string s1 = deep::string(context, str1);
    deep::string s2 = deep::string(context, str2);
    deep::string s3 = deep::string(context, str3);
    deep::string s4 = deep::string(context, str4);

    if (!deep::string::equals(str1, str2))
    {
        return 10;
    }

    if (deep::string::equals(str1, str3))
    {
        return 11;
    }

    if (deep::string::equals(str2, str4))
    {
        return 12;
    }

    if (!s1.equals(s2))
    {
        return 13;
    }

    if (s1.equals(s3))
    {
        return 14;
    }

    if (s2.equals(s4))
    {
        return 15;
    }

    if (!s1.append(DEEP_TEXT_UTF8('!')))
    {
        return 16;
    }

    if (!s1.equals(s4))
    {
        return 17;
    }

    deep::string empty = deep::string(context);

    if (!empty.append(DEEP_TEXT_UTF8('a')))
    {
        return 18;
    }

    if (empty[0] != DEEP_TEXT_UTF8('a'))
    {
        return 19;
    }

    deep::string false_str = deep::string::from(context, false);
    deep::string true_str  = deep::string::from(context, true);
    deep::string uint_str  = deep::string::from(context, static_cast<deep::uint64>(71));

    if (!false_str.equals(DEEP_TEXT_UTF8("false")))
    {
        return 20;
    }

    if (!true_str.equals(DEEP_TEXT_UTF8("true")))
    {
        return 21;
    }

    if (!uint_str.equals(DEEP_TEXT_UTF8("71")))
    {
        return 22;
    }

    if (!uint_str.insert(DEEP_TEXT_UTF8("uint_")))
    {
        return 23;
    }

    if (!uint_str.equals(DEEP_TEXT_UTF8("uint_71")))
    {
        return 24;
    }

    deep::string int_str1    = deep::string::from(context, static_cast<deep::int64>(32));
    deep::string int_str2    = deep::string::from(context, static_cast<deep::int64>(-64));
    deep::string double_str1 = deep::string::from(context, 127.64);
    deep::string double_str2 = deep::string::from(context, -5002.46);

    if (!int_str1.equals(DEEP_TEXT_UTF8("32")))
    {
        return 25;
    }

    if (!int_str2.equals(DEEP_TEXT_UTF8("-64")))
    {
        return 26;
    }

    printf("%s\n", *false_str);
    printf("%s\n", *true_str);
    printf("%s\n", *uint_str);
    printf("%s\n", *int_str1);
    printf("%s\n", *int_str2);
    printf("%s\n", *double_str1);
    printf("%s\n", *double_str2);

    return 0;
}
