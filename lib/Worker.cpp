// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <Apology/Worker.hpp>

using namespace Apology;

Worker::Worker(Theron::Framework &framework):
    Theron::Actor(framework)
{
    //NOP
}

Worker::~Worker(void)
{
    _inputs.clear();
    _outputs.clear();
}
