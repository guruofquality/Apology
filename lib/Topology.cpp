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
#include <Apology/Worker.hpp>
#include <ApologyVecUtils.hpp>

using namespace Apology;

Topology::Topology(void)
{
    //NOP
}

Topology::~Topology(void)
{
    this->clear_all();
}

void Topology::clear_all(void)
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

std::vector<Port> Topology::_resolve_ports(const Port &port, const bool do_source)
{
    std::vector<Port> ports;

    //check for weird conditions
    if (not port.elem)
    {
        throw std::runtime_error("resolve ports total inception error!");
    }

    //check if this is a worker
    if (dynamic_cast<Worker *>(port.elem))
    {
        ports.push_back(port);
    }

    //otherwise, recurse into the sub topology
    else for (size_t i = 0; i < _flows.size(); i++)
    {
        const Flow &flow = _flows[i];
        Port found_port;

        if (
            do_source and
            flow.dst.elem != this and //flow to self
            flow.dst.index == port.index //matching port
        ){
            found_port = flow.src;
        }

        if (
            not do_source and
            flow.src.elem != this and //flow to self
            flow.src.index == port.index //matching port
        ){
            found_port = flow.dst;
        }

        if (found_port.elem and dynamic_cast<Worker *>(found_port.elem))
        {
            ports.push_back(found_port);
        }

        if (found_port.elem and dynamic_cast<Topology *>(found_port.elem))
        {
            Topology *topology = dynamic_cast<Topology *>(found_port.elem);
            extend(ports, topology->_resolve_ports(found_port, do_source));
        }
    }

    return ports;
}

std::vector<Flow> Topology::_resolve_flows(void)
{
    std::vector<Flow> flat_flows;

    for (size_t i = 0; i < _flows.size(); i++)
    {
        const Flow &flow = _flows[i];

        //ignore flows to self
        if (flow.src.elem == this) continue;
        if (flow.dst.elem == this) continue;

        std::vector<Port> srcs;
        std::vector<Port> dsts;

        //use the port if its a worker
        if (dynamic_cast<Worker *>(flow.src.elem))
        {
            srcs.push_back(flow.src);
        }

        //otherwise traverse the port
        if (dynamic_cast<Topology *>(flow.src.elem))
        {
            srcs = dynamic_cast<Topology *>(flow.src.elem)->_resolve_ports(flow.src, true/*src*/);
        }

        //use the port if its a worker
        if (dynamic_cast<Worker *>(flow.src.elem))
        {
            dsts.push_back(flow.dst);
        }

        //otherwise traverse the port
        if (dynamic_cast<Topology *>(flow.dst.elem))
        {
            dsts = dynamic_cast<Topology *>(flow.dst.elem)->_resolve_ports(flow.dst, false/*dst*/);
        }

        //append all the actual flows resolved here
        for (size_t s = 0; s < srcs.size(); s++)
        {
            for (size_t d = 0; d < dsts.size(); d++)
            {
                flat_flows.push_back(Flow(srcs[s], dsts[d]));
            }
        }
    }

    //get a list of unique sub-topolgies
    std::vector<Topology *> sub_topologies;
    for (size_t i = 0; i < _topologies.size(); i++)
    {
        remove_one(sub_topologies, _topologies[i]);
        sub_topologies.push_back(_topologies[i]);
    }

    //add to the list of sub-topolgies involved in flows
    for (size_t i = 0; i < _flows.size(); i++)
    {
        const Flow &flow = _flows[i];

        if (flow.src.elem and dynamic_cast<Topology *>(flow.src.elem))
        {
            remove_one(sub_topologies, flow.src.elem);
            sub_topologies.push_back(dynamic_cast<Topology *>(flow.src.elem));
        }

        if (flow.dst.elem and dynamic_cast<Topology *>(flow.dst.elem))
        {
            remove_one(sub_topologies, flow.dst.elem);
            sub_topologies.push_back(dynamic_cast<Topology *>(flow.dst.elem));
        }
    }

    //now recurse through all sub-topologies
    for (size_t i = 0; i < sub_topologies.size(); i++)
    {
        Topology *topology = sub_topologies[i];
        extend(flat_flows, topology->_resolve_flows());
    }

    return flat_flows;
}
