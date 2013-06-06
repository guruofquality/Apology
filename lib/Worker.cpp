// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <Apology/Worker.hpp>

using namespace Apology;

Worker::Worker(void)
{
    //NOP
}

Worker::~Worker(void)
{
    _inputs.clear();
    _outputs.clear();
}

void Worker::set_actor(Theron::Actor *actor)
{
    _actor = actor;
}

THERON_DEFINE_REGISTERED_MESSAGE(Apology::WorkerTopologyMessage);
