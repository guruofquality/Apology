// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_APOLOGY_WORKER_HPP
#define INCLUDED_APOLOGY_WORKER_HPP

#include <Apology/Config.hpp>
#include <Apology/Port.hpp>
#include <Theron/Actor.h>
#include <vector>

#ifdef _MSC_VER //remove some template export warnings
APOLOGY_EXTERN template class APOLOGY_API std::vector<Apology::Worker *>;
APOLOGY_EXTERN template class APOLOGY_API std::vector<std::vector<Apology::Port> >;
#endif

namespace Apology
{

/*!
 * A derived worker should register a message handler
 * for this message to get an update about topology.
 */
struct APOLOGY_API WorkerTopologyMessage
{
    //empty
};

/*!
 * A worker represents a unit of computation.
 * A worker contains an actor.
 * As part of being in a topology:
 * Arbitrary messages may be accepted from upstream ports
 * and arbitrary messages may be posted to downstream ports.
 */
struct APOLOGY_API Worker : Base
{
    //! Create a new worker
    Worker(void);

    //! Destroy the worker
    virtual ~Worker(void);

    //! Set the active actor
    void set_actor(Theron::Actor *actor);

    //! Get the active actor
    Theron::Actor *get_actor(void) const;

    //! Get the number of input ports
    size_t get_num_inputs(void) const;

    //! Get the number of output ports
    size_t get_num_outputs(void) const;

    /*!
     * Send a message to all downstream blocks on this output port.
     * \param index the output port index
     * \msg the message (must have index member)
     */
    template <typename Message>
    void post_downstream(const size_t index, const Message &msg) const;

    /*!
     * Send a message to all upstream blocks on this input port.
     * \param index the input port index
     * \msg the message (must have index member)
     */
    template <typename Message>
    void post_upstream(const size_t index, const Message &msg) const;

    std::vector<std::vector<Port> > _inputs;
    std::vector<std::vector<Port> > _outputs;
    Theron::Actor *_actor;
};

THERON_FORCEINLINE Theron::Actor *Worker::get_actor(void) const
{
    return _actor;
}

THERON_FORCEINLINE size_t Worker::get_num_inputs(void) const
{
    return _inputs.size();
}

THERON_FORCEINLINE size_t Worker::get_num_outputs(void) const
{
    return _outputs.size();
}

template <typename Message>
THERON_FORCEINLINE void Worker::post_downstream(const size_t index, const Message &msg) const
{
    Message message = msg;
    for (size_t i = 0; i < _outputs[index].size(); i++)
    {
        const Port &port = _outputs[index][i];
        message.index = port.index;
        Theron::Actor *actor = reinterpret_cast<Worker *>(port.elem)->get_actor();
        actor->GetFramework().Send(message, Theron::Address::Null(), actor->GetAddress());
    }
}

template <typename Message>
THERON_FORCEINLINE void Worker::post_upstream(const size_t index, const Message &msg) const
{
    Message message = msg;
    for (size_t i = 0; i < _inputs[index].size(); i++)
    {
        const Port &port = _inputs[index][i];
        message.index = port.index;
        Theron::Actor *actor = reinterpret_cast<Worker *>(port.elem)->get_actor();
        actor->GetFramework().Send(message, Theron::Address::Null(), actor->GetAddress());
    }
}

} //namespace Apology

#include <Theron/Register.h>

THERON_DECLARE_REGISTERED_MESSAGE(Apology::WorkerTopologyMessage);

#endif /*INCLUDED_APOLOGY_WORKER_HPP*/
