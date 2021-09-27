#pragma once

#include "shrinkpimpl.hpp"

class Foo
{
    class impl;
    pimpl<impl> impl;
};