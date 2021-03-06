/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#include <yarp/dev/DriverLinkCreator.h>

yarp::dev::DriverLinkCreator::DriverLinkCreator(const std::string& name, PolyDriver& source) :
        name(name)
{
    holding.link(source);
}

yarp::dev::DriverLinkCreator::~DriverLinkCreator()
{
    holding.close();
}
