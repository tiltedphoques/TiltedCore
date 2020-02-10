#pragma once

namespace TiltedPhoques
{
    struct Initializer
    {
        template<class Func>
        Initializer(const Func& aFunc)
        {
            aFunc();
        }
    };
}
