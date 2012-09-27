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

namespace Apology
{

struct APOLOGY_API Executor : Theron::Actor
{
    //! Create a new Executor
    Executor(Topology &topology);

    //! Destroy the executor actor
    virtual ~Executor(void);

    /*!
     * Commit any topological changes to the design.
     * Call this method after calling changing connections.
     * This will add/remove any connections from the previous state,
     * and send an update topology message to any changed blocks.
     */
    void commit(void);

    /*!
     * Post a message to all blocks in the topology.
     */
    void post_msg(const Wax &msg);
};

} //namespace Apology

#endif /*INCLUDED_APOLOGY_EXECUTOR_HPP*/
