// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_APOLOGY_TOPOLOGY_HPP
#define INCLUDED_APOLOGY_TOPOLOGY_HPP

#include <Apology/Config.hpp>
#include <Apology/Flow.hpp>
#include <vector>

APOLOGY_EXTERN template class APOLOGY_API std::vector<Apology::Topology *>;
APOLOGY_EXTERN template class APOLOGY_API std::vector<Apology::Flow>;

namespace Apology
{

/*!
 * A topology describes a message flow for workers.
 */
struct APOLOGY_API Topology : Base
{
    //! Create a new Topology
    Topology(void);

    //! Destroy the topology
    virtual ~Topology(void);

    /*!
     * Add a child topology to this parent.
     * Normally the hierarchy is implied by add flow:
     * This routine is reserved for a topology without IO.
     */
    void add_topology(Topology *topology);

    //! Remove a child topology from this parent.
    void remove_topology(Topology *topology);

    //! Adds a new flow to the topology
    void add_flow(const Flow &flow);

    //! Remove a flow from the topology
    void remove_flow(const Flow &flow);

    /*!
     * Reset this topology to factory state.
     * In other words, remove all flows and sub-topologies.
     */
    void clear_all(void);

    /*!
     * Call commit on the top level executor.
     * Only call this when topology has been committed to a design.
     */
    void commit(void);

    Executor *_executor;
    std::vector<Topology *> _topologies;
    std::vector<Flow> _flows;
    std::vector<Port> _resolve_ports(const Port &port, const bool);
    std::vector<Flow> _resolve_flows(Executor *executor);
};

} //namespace Apology

#endif /*INCLUDED_APOLOGY_TOPOLOGY_HPP*/
