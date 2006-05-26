// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#ifndef _YARP2_USERDOC_
#define _YARP2_USERDOC_

/**
 * @mainpage Welcome to YARP
 *
 * @section welcome_disclaimer Disclaimer
 *
 * \code
       Through Me Pass into the Painful City,
       Through Me Pass into Eternal Grief,
       Through Me Pass among the Lost People.
       Justice Moved My Master-Builder:
       Heavenly Power First Fashioned Me
       With Highest Wisdom and with Primal Love.
       Before Me Nothing Was Created That
       Was Not Eternal, and I Last Eternally.
       All Hope Abandon, You Who Enter Here.
 * \endcode
 *
 * @section welcome_topics Topics
 *
 * Need help installing and compiling YARP?  See @ref install.
 *
 * Want to start using the library?  Start with @ref yarp_os.
 *
 */


/**
 * @page install Installation Tips
 *
 * @section install_start Getting started
 *
 * YARP is available from http://yarp0.sourceforge.net
 *
 *
 *
 */

/**
 * @page yarp_os The YARP OS library
 *
 * @section intro_sec Introduction
 *
 * Welcome to the YARP OS library.  This library interfaces
 * with your operating system and provides some basic services.
 * We give you
 * \link yarp::os::Thread Thread\endlink, 
 * \link yarp::os::Semaphore Semaphore\endlink, and 
 * \link yarp::os::Time Time\endlink
 * services just in case
 * you don't have them, but our main goal is to give you easy network
 * communication using the YARP 
 * \link yarp::os::Port Port\endlink
 * Network.
 * 
 * The links at the top of this page let you explore the classes
 * provided in the YARP OS library.  To install and test yarp,
 * see our website, http://yarp0.sourceforge.net
 *
 * @section install_sec What is a Port?
 *
 * A \link yarp::os::Port Port\endlink is an object that can read and
 * write values to peer objects spread throughout a network of
 * computers.  You can create them in your program, and then add and
 * remove connections either from that program, from the command line,
 * or from another program.
 * Ports are specialized for streaming communication, such as camera
 * images or motor commands.  You can switch network protocols for any
 * or all your connections without changing a line of code.
 *
 * @section example_sec A simple code example
 *
 * Here we work through an example of using YARP communication.
 * First, here are two programs, a sender and receiver, let's call
 * them sender.cpp and receiver.cpp
 *
 * @subsection example_sender A program for sending a message
 * \code
 // source for sender.cpp
 #include <yarp/os/Network.h>
 #include <yarp/os/Port.h>
 #include <yarp/os/Bottle.h>
 #include <yarp/os/Time.h>
 #include <stdio.h>
 using namespace yarp::os;
 int main() {
 Network::init();
 Bottle bot1; 
 bot1.addString("testing"); // a simple message
 Port output;
 output.open("/out");
 for (int i=0; i<100; i++) {
 output.write(bot1);
 printf("Sent message: %s\n", bot1.toString().c_str());
 bot1.addInt(i); // change the message for next time
 Time::delay(1);
 }
 output.close();
 Network::fini();
 return 0;
 }
 * \endcode
 *
 * @subsection example_receiver A program for receiving a message
 *
 * \code
 // source for receiver.cpp
 #include <yarp/os/Network.h>
 #include <yarp/os/Port.h>
 #include <yarp/os/Bottle.h>
 #include <stdio.h>
 using namespace yarp::os;
 int main() {
 Network::init();
 Bottle bot2;
 Port input;
 input.open("/in");
 input.read(bot2);
 printf("Got message: %s\n", bot2.toString().c_str());
 input.close();
 Network::fini();
 return 0;
 }
 * \endcode
 *
 * @subsection example_compiling Compiling the examples
 *
 * To compile these programs you need two libraries: yarp and ace.
 * These instructions assume you have installed them - if not, see
 * their websites for instructions.  The source of these programs
 * and a makefile are in the directory src/libYARP_OS2/examples
 *
 * If you're on a UNIX machine, you can compile with:
 * \code
 g++ receiver.cpp -o receiver -lACE -lYARP_OS
 g++ sender.cpp -o sender -lACE -lYARP_OS
 * \endcode
 *
 * On windows, you'll need to set up projects and set up include
 * paths and libraries appropriately.
 *
 * @subsection example_running Running the examples
 *
 * On UNIX, on four separate consoles, do:
 * \code
 yarp server
 ./sender
 ./receiver
 yarp connect /out /in
 * \endcode
 *
 * (You may have to give a path to wherever yarp is compiled if it is
 * not in your path). The process on windows in similar.
 *
 */


#endif
