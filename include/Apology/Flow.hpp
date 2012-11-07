// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#ifndef INCLUDED_APOLOGY_FLOW_HPP
#define INCLUDED_APOLOGY_FLOW_HPP

#include <Apology/Config.hpp>
#include <Apology/Port.hpp>

namespace Apology
{

/*!
 * A flow represents a data path between a source port and a destination port.
 */
struct APOLOGY_API Flow
{
    //! Create an unitialized flow
    Flow(void);

    //! Create a flow from source and destination
    Flow(const Port &src, const Port &dst);

    //! The source port (provides data)
    Port src;

    //! The sink port (accepts data)
    Port dst;
};

//! a comparison operator overload for flows
APOLOGY_API bool operator==(const Flow &lhs, const Flow &rhs);

} //namespace Apology

#endif /*INCLUDED_APOLOGY_FLOW_HPP*/
