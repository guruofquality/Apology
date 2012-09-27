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

#ifndef INCLUDED_APOLOGY_TOPOLOGY_HPP
#define INCLUDED_APOLOGY_TOPOLOGY_HPP

#include <Apology/Config.hpp>
#include <Apology/Flow.hpp>
#include <Theron/Actor.h>

namespace Apology
{

/*!
 * A topology describes a message flow for workers.
 */
struct APOLOGY_API Topology : Theron::Actor
{
    //! Create a new Topology
    Topology(Theron::Framework &framework);

    //! Destroy the topology actor
    virtual ~Topology(void);

    /*!
     * Add a child topology to this parent.
     * Normally the hierarchy is implied by add flow:
     * This routine is reserved for a topology without IO.
     */
    void add_topology(const Topology &topology);

    //! Remove a child topology from this parent.
    void remove_topology(const Topology &topology);

    //! Adds a new flow to the topology
    void add_flow(const Flow &flow);

    //! Remove a flow from the topology
    void remove_flow(const Flow &flow);

    /*!
     * Reset this topology to factory state.
     * In other words, remove all flows and sub-topologies.
     */
    void clear_all(void);
};

} //namespace Apology

#endif /*INCLUDED_APOLOGY_TOPOLOGY_HPP*/
