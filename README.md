greyrockServer
==============

This is a test project to create a domain specific server for REST that uses a high level programming language (like Python or Ruby) over a thin interface written in C/C++.

The thin interface on top will be used to configure the system and provide the glue for the lower level C/C++ networking componenets.
The interface will be flexible enough to allow for simple webapps, or to create complex gateway applications with functionality like Rate Limiting, Proxying Requests, and performing authentication.
