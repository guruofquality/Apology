// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <boost/test/unit_test.hpp>
#include <Apology/Executor.hpp>
#include <Apology/Topology.hpp>
#include <Apology/Worker.hpp>
#include <iostream>

struct TestMessage
{
    //empty
};

struct MyActor : Theron::Actor
{
    MyActor(Theron::Framework &framework):
        Theron::Actor(framework)
    {
        this->RegisterHandler(this, &MyActor::handle_topology);
        this->RegisterHandler(this, &MyActor::handle_test);
    }

    void handle_topology(const Apology::WorkerTopologyMessage &message, const Theron::Address from)
    {
        std::cout << "handle_topology " << size_t(this) << std::endl;
        this->Send(message, from); //ACK
    }

    void handle_test(const TestMessage &message, const Theron::Address from)
    {
        std::cout << "handle_test " << size_t(this) << std::endl;
        this->Send(message, from); //ACK
    }
};

struct MyWorker : Apology::Worker
{
    MyWorker(Theron::Framework &framework)
    {
        this->set_actor(new MyActor(framework));
    }

    ~MyWorker(void)
    {
        delete this->get_actor();
    }
};

BOOST_AUTO_TEST_CASE(test_make_topology)
{
    Apology::Topology topology;
}

BOOST_AUTO_TEST_CASE(test_make_worker)
{
    Apology::Worker w;
}

BOOST_AUTO_TEST_CASE(test_make_executor)
{
    Apology::Topology topology;
    Apology::Executor executor(&topology);
}

BOOST_AUTO_TEST_CASE(test_simple_commit)
{
    std::cout << "about to make theron framework" << std::endl;
    Theron::Framework framework(1/*thread*/);
    std::cout << "about to make some of my workers" << std::endl;
    MyWorker src(framework);
    MyWorker dst(framework);
    Apology::Flow flow(Apology::Port(&src, 0), Apology::Port(&dst, 0));

    Apology::Topology topology;
    std::cout << "adding flow to topology" << std::endl;
    topology.add_flow(flow);
    std::cout << "...done!" << std::endl;

    Apology::Executor executor(&topology);
    std::cout << "calling executor commit" << std::endl;
    executor.commit();
    std::cout << "...done!" << std::endl;

    std::cout << "post a message to all workers" << std::endl;
    executor.post_all(TestMessage());
    std::cout << "...done!" << std::endl;
}
