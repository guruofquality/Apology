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

#include <boost/test/unit_test.hpp>
#include <Apology/Executor.hpp>
#include <Apology/Topology.hpp>
#include <Apology/Worker.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_make_topology)
{
    Apology::Topology topology;
}

BOOST_AUTO_TEST_CASE(test_make_worker)
{
    Theron::Framework framework(1/*thread*/);
    Apology::Worker *w = new Apology::Worker(framework);
    delete w;
}

BOOST_AUTO_TEST_CASE(test_make_executor)
{
    Apology::Topology topology;
    Apology::Executor executor(&topology);
}

BOOST_AUTO_TEST_CASE(test_simple_commit)
{
    Theron::Framework framework(1/*thread*/);
    Apology::Worker *src = new Apology::Worker(framework);
    Apology::Worker *dst = new Apology::Worker(framework);
    Apology::Flow flow(Apology::Port(src, 0), Apology::Port(dst, 0));

    Apology::Topology topology;
    topology.add_flow(flow);

    Apology::Executor executor(&topology);
    executor.commit();

    delete src;
    delete dst;
}
