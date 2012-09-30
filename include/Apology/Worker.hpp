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

#ifndef INCLUDED_APOLOGY_WORKER_HPP
#define INCLUDED_APOLOGY_WORKER_HPP

#include <Apology/Config.hpp>
#include <Apology/Port.hpp>
#include <Theron/Actor.h>
#include <vector>

APOLOGY_EXTERN template class APOLOGY_API std::vector<Apology::Worker *>;
APOLOGY_EXTERN template class APOLOGY_API std::vector<std::vector<Apology::Port> >;

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
 * As part of being in a topology:
 * Arbitrary messages may be accepted from upstream ports
 * and arbitrary messages may be posted to downstream ports.
 */
struct APOLOGY_API Worker : Base, Theron::Actor
{
public:
    //! Create a new worker actor
    Worker(Theron::Framework &framework);

    //! Destroy the worker actor
    virtual ~Worker(void);

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
};

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
        reinterpret_cast<Worker *>(port.elem)->Push(message, Theron::Address());
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
        reinterpret_cast<Worker *>(port.elem)->Push(message, Theron::Address());
    }
}

} //namespace Apology

#endif /*INCLUDED_APOLOGY_WORKER_HPP*/
