// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <Apology/Flow.hpp>

using namespace Apology;

Flow::Flow(void)
{
    //NOP
}

Flow::Flow(const Port &src, const Port &dst):
    src(src), dst(dst)
{
    //NOP
}

bool Apology::operator==(const Flow &lhs, const Flow &rhs)
{
    return (lhs.src == rhs.src and lhs.dst == rhs.dst);
}
