// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_APOLOGY_EXECUTOR_HPP
#define INCLUDED_APOLOGY_EXECUTOR_HPP

#include <Apology/Config.hpp>
#include <Apology/Topology.hpp>
#include <Apology/Worker.hpp>
#include <Apology/Flow.hpp>
#include <Theron/Receiver.h>
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

    //! Get a const iterator to the workers in this executor
    const std::vector<Worker *> &get_workers(void) const;

    /*!
     * Get a const iterator to the flattened flows in this executor.
     * All ports contain pointers to workers and not topologies.
     */
    const std::vector<Flow> &get_flat_flows(void) const;

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
        Theron::Actor *actor = _worker_set[i]->get_actor();
        actor->GetFramework().Send(msg, _receiver.GetAddress(), actor->GetAddress());
    }

    size_t outstandingCount(_worker_set.size());
    while (outstandingCount != 0)
    {
        outstandingCount -= _receiver.Wait(outstandingCount);
    }
}

} //namespace Apology

#endif /*INCLUDED_APOLOGY_EXECUTOR_HPP*/
