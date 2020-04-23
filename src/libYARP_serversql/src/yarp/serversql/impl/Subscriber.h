/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * Copyright (C) 2006-2010 RobotCub Consortium
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SERVERSQL_IMPL_SUBSCRIBER_H
#define YARP_SERVERSQL_IMPL_SUBSCRIBER_H

#include <yarp/name/NameService.h>
#include <yarp/serversql/impl/ConnectThread.h>

#include <string>
#include <yarp/os/Vocab.h>
#include <yarp/os/NameStore.h>
#include <yarp/os/NameSpace.h>


namespace yarp {
namespace serversql {
namespace impl {

/**
 * Abstract interface for maintaining persistent connections.
 */
class Subscriber :
        public yarp::name::NameService
{
public:
    Subscriber() :
            store(nullptr),
            silent(false),
            delegate(nullptr)
    {
    }

    void setStore(yarp::os::NameStore& store)
    {
        this->store = &store;
    }

    yarp::os::NameStore *getStore()
    {
        return store;
    }

    void setSilent(bool flag)
    {
        this->silent = flag;
    }

    void clear()
    {
        manager.clear();
    }

    void connect(const std::string& src,
                 const std::string& dest)
    {
        manager.connect(src,dest);
    }

    void disconnect(const std::string& src,
                    const std::string& dest,
                    bool srcDrop)
    {
        manager.disconnect(src,dest,srcDrop);
    }

    virtual bool addSubscription(const std::string& src,
                                 const std::string& dest,
                                 const std::string& mode) = 0;

    virtual bool removeSubscription(const std::string& src,
                                    const std::string& dest) = 0;

    virtual bool listSubscriptions(const std::string& src,
                                   yarp::os::Bottle& reply) = 0;

    virtual bool welcome(const std::string& port, int activity) = 0;

    virtual bool setTopic(const std::string& port,
                          const std::string& structure, bool active) = 0;

    virtual bool listTopics(yarp::os::Bottle& topics) = 0;

    virtual bool setType(const std::string& family,
                         const std::string& structure,
                         const std::string& value) = 0;

    virtual std::string getType(const std::string& family,
                                          const std::string& structure) = 0;

    bool apply(yarp::os::Bottle& cmd,
               yarp::os::Bottle& reply,
               yarp::os::Bottle& event,
               const yarp::os::Contact& remote) override;

    void onEvent(yarp::os::Bottle& event) override
    {
    }

    int replyCode(bool flag) {
        return flag ? yarp::os::createVocab('o', 'k')
                    : yarp::os::createVocab('f', 'a', 'i', 'l');
    }

    void setDelegate(yarp::os::NameSpace *delegate)
    {
        this->delegate = delegate;
    }

    yarp::os::NameSpace *getDelegate()
    {
        return delegate;
    }

private:
    yarp::os::NameStore *store;
    ConnectManager manager;
    bool silent;
    yarp::os::NameSpace *delegate;
};

} // namespace impl
} // namespace serversql
} // namespace yarp


#endif // YARP_SERVERSQL_IMPL_SUBSCRIBER_H
