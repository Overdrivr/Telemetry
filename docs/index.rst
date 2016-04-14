.. Telemetry documentation master file, created by
   sphinx-quickstart on Thu Apr 14 11:36:29 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Telemetry's documentation!
=====================================

The Telemetry project is a collection of tools for remote data-visualization and communication with embedded devices.

At its core, Telemetry implements a communication protocol for exchanging data between a computer and any embedded platform.
Extra tools are build around this protocol to provide a fun and easy way to communicate with the device from a computer in real-time.

The Telemetry project is constituted of different libraries at the moment:

* Protocol implementations

  * Telemetry: The original C/C++ implementation of the protocol that runs on embedded platforms (Arduino, Mbed)
  * Pytelemetry: A python package for the desktop (Windows, Mac OS, Linux) that implements the same exact protocol

* Desktop Tools

  * Pytelemetrycli: A command line interface where live plots on received data can be opened from a single command.
  Also features commands for reconfiguring device's paramemeters in real-time, logging, network analysis, etc.
  Implemented in python, runs on Windows, Mac OS and Linux

Contents:


.. toctree::
   :maxdepth: 4



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
