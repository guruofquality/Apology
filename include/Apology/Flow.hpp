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
