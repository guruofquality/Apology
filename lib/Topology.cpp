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

#include <Apology/Topology.hpp>
#include <ApologyVecUtils.hpp>

using namespace Apology;

Topology::Topology(void)
{
    //NOP
}

Topology::~Topology(void)
{
    _topologies.clear();
    _flows.clear();
}

void Topology::add_topology(Topology *topology)
{
    _topologies.push_back(topology);
}

void Topology::remove_topology(Topology *topology)
{
    if (not remove_one(_topologies, topology))
    {
        throw std::runtime_error("Topology::remove_topology could not find topology");
    }
}

void Topology::add_flow(const Flow &flow_)
{
    //dont store container when the elem is this topology
    Flow flow = flow_;
    if (flow.src.elem == this) flow.src.container = Wax();
    if (flow.dst.elem == this) flow.dst.container = Wax();
    _flows.push_back(flow);
}

void Topology::remove_flow(const Flow &flow)
{
    if (not remove_one(_flows, flow))
    {
        throw std::runtime_error("Topology::remove_flow could not find flow");
    }
}
