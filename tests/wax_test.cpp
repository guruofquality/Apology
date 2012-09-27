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
#include <Apology/Wax.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_wax_size)
{
    BOOST_CHECK(Apology::Wax::buff_size >= sizeof(boost::shared_ptr<void *>));
    BOOST_CHECK(Apology::Wax::buff_size >= sizeof(boost::intrusive_ptr<void *>));
    BOOST_CHECK(Apology::Wax::buff_size >= (sizeof(boost::intrusive_ptr<void *>)*3 + sizeof(long long)));
}

BOOST_AUTO_TEST_CASE(test_wax_assign)
{
    Apology::Wax x;
    BOOST_CHECK(x.empty());

    x = int(3);
    BOOST_CHECK(not x.empty());

    BOOST_CHECK_EQUAL(x.cast<int>(), 3);
    Apology::Wax y = x;
    BOOST_CHECK_EQUAL(y.cast<int>(), 3);

    y = int(4);
    BOOST_CHECK_EQUAL(x.cast<int>(), 3);
    BOOST_CHECK_EQUAL(y.cast<int>(), 4);

    x.reset();
    BOOST_CHECK(x.empty());
    BOOST_CHECK_EQUAL(y.cast<int>(), 4);
}

struct simple_something
{
    simple_something(const int x)
    {
        std::cout << "simple_something" << std::endl;
        value = x;
    }

    ~simple_something(void)
    {
        std::cout << "~simple_something" << std::endl;
    }

    int value;
};

BOOST_AUTO_TEST_CASE(test_wax)
{
    Apology::Wax x;
    Apology::Wax y(int(3));
    BOOST_CHECK_EQUAL(y.cast<int>(), 3);

    Apology::Wax ss_wax;
    {
        boost::shared_ptr<simple_something> ss(new simple_something(42));
        ss_wax = Apology::Wax(ss);
        BOOST_CHECK_EQUAL(ss->value, 42);
        BOOST_CHECK_EQUAL(ss_wax.cast<boost::shared_ptr<simple_something> >()->value, 42);
    }
    BOOST_CHECK_EQUAL(ss_wax.cast<boost::shared_ptr<simple_something> >()->value, 42);
    Apology::Wax ss_wax2 = ss_wax;
    BOOST_CHECK_EQUAL(ss_wax2.cast<boost::shared_ptr<simple_something> >()->value, 42);
}
