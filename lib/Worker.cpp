//
// Copyright 2012 Josh Blum
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <Apology/Worker.hpp>
#include <ApologyVecUtils.hpp>

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
/*
void Worker::_handle_flow(
    const WorkerFlowMessage &message,
    const Theron::Address from
){
    const Flow &flow = message.flow;

    switch (message.action)
    {
    case WorkerFlowMessage::SRC_ADD:
        vector_vector_add(_outputs, flow.src.index, flow.dst);
        break;

    case WorkerFlowMessage::DST_ADD:
        vector_vector_add(_inputs, flow.dst.index, flow.src);
        break;

    case WorkerFlowMessage::SRC_REM:
        vector_vector_remove(_outputs, flow.src.index, flow.dst);
        break;

    case WorkerFlowMessage::DST_REM:
        vector_vector_remove(_inputs, flow.dst.index, flow.src);
        break;
    }

    this->Send(message, from); //ACK
}
*/
