// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <Apology/Port.hpp>

using namespace Apology;

Port::Port(void)
{
    elem = NULL;
    index = 0;
}

Port::Port(Base *elem, const size_t index, Wax container):
    elem(elem), index(index), container(container)
{
    //NOP
}

bool Apology::operator==(const Port &lhs, const Port &rhs)
{
    return (lhs.elem == rhs.elem and lhs.index == rhs.index);
}
