.. Telemetry documentation master file, created by
   sphinx-quickstart on Thu Apr 14 11:36:29 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Telemetry's documentation!
=====================================

The ``Telemetry`` project is a collection of tools for *remote data-visualization
and communication* with embedded devices.

.. image:: https://raw.githubusercontent.com/Overdrivr/Telemetry/master/docs/pubsub_overview.png


At its core, `Telemetry` is a communication protocol.

Data is exchanged on named channels, called *topics* (ex : `foo`, `bar` and `qux` on the figure above).

Sending data is called *publishing*.

.. code-block:: cpp

    Telemetry TM;
    int32_t i = 123;

    TM.pub_i32("foo", i);


Receiving data is called *subscribing*.
A variable attached to a topic will be updated each time new data is received under this topic.

.. code-block:: cpp

    Telemetry TM;
    float throttle;

    TM.attach_f32_to("throttle", &throttle);

    for(;;) {
       TM.update();
    }


Extra tools are build around this protocol to provide a fun and easy way to communicate with the device from a computer in real-time.


The Telemetry project is constituted of different libraries at the moment:

* **Protocol implementations**

  * ``Telemetry``: Portable C/C++ implementation of the protocol. Runs on embedded platforms (``Arduino``, ``Mbed``, etc.).
  * ``Pytelemetry``: Python implementation of the protocol. Runs on Windows, Mac OS, Linux

* **Desktop Tools**

  * ``Pytelemetrycli``: Smart command line interface. Open **live plots** on received data from a single command,
  reconfigure device in real-time, logging, network analysis, etc.
  Runs on Windows, Mac OS and Linux

Contents:


.. toctree::
   :maxdepth: 4



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
