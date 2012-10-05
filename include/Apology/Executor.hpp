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

#ifndef INCLUDED_APOLOGY_EXECUTOR_HPP
#define INCLUDED_APOLOGY_EXECUTOR_HPP

#include <Apology/Config.hpp>
#include <Apology/Topology.hpp>
#include <Apology/Worker.hpp>
#include <Apology/Flow.hpp>
#include <vector>

namespace Apology
{

struct APOLOGY_API Executor
{
    //! Create a new Executor
    Executor(Topology *topology);

    //! Destroy the executor actor
    virtual ~Executor(void);

    /*!
     * Commit any topological changes to the design.
     * Call this method after changing flows or sub-topologies.
     * This will add/remove any flows from the previous state,
     * and send an update topology message to any changed workers.
     */
    void commit(void);

    /*!
     * Post a message to all blocks in the topology.
     */
    template <typename Message>
    void post_all(const Message &msg);

    Topology *_topology;
    std::vector<Flow> _flat_flows;
    std::vector<Worker *> _worker_set;
    Theron::Receiver _receiver;
};

template <typename Message>
THERON_FORCEINLINE void Executor::post_all(const Message &msg)
{
    for (size_t i = 0; i < _worker_set.size(); i++)
    {
        _worker_set[i]->Push(msg, _receiver.GetAddress());
        _receiver.Wait();
    }
}

} //namespace Apology

#endif /*INCLUDED_APOLOGY_EXECUTOR_HPP*/
