[![Stories in Ready](https://badge.waffle.io/Overdrivr/pytelemetrycli.svg?label=ready&title=Ready)](http://waffle.io/Overdrivr/pytelemetrycli)
## Overview
`Telemetry` provides effortless communication between a computer and an embedded device.

Telemetry is a lightweight, portable, fast and error-resilient point-to-point protocol. It is implemented in C language with an equivalent in Python (Pytelemetry).

![Overview](https://raw.githubusercontent.com/Overdrivr/Telemetry/master/pubsub_overview.png)

Data is exchanged on named channels, called *topics*. `foo`, `bar` and `qux` are all topics on the figure above.

`Telemetry` lets you attach your own C function to a topic. Each time this specific topic is received, your C function will be called and you will receive the associated data as an input parameter.

## Why using it ?

Telemetry is for you if :

* you are constantly re-writing custom protocols on top of the serial port
* you need a **reliable** and **error-tolerant** communication protocol for an application
* you are using `printf` to debug your embedded application (and looking for a better alternative)
* you want to finely tune some parameter on the device without loosing time compiling & flashing over and over
* you want to **plot** parameters of your embedded application in **real-time**

## Python implementation [![PyPI version](https://badge.fury.io/py/pytelemetry.svg)](https://badge.fury.io/py/pytelemetry)

[`pytelemetry`](https://github.com/Overdrivr/pytelemetry) is the python equivalent of this protocol, and is 100% compatible.
You can use it to write simple python scripts that communicate with the device, to send commands and update parameters in real time.
It is highly suitable for remote control of robots, RC cars, etc.  

## The Command Line Interface [![PyPI version](https://badge.fury.io/py/pytelemetrycli.svg)](https://badge.fury.io/py/pytelemetrycli)

[`pytelemetrycli`](https://github.com/Overdrivr/pytelemetrycli) is an awesome command line interface that allows direct communication with the device.

Directly in a terminal, with a few commands, you can :
* list all received topics
* print samples from a given topic
* publish data on a topic
* open high-performance graphs that plots data from the device in real-time
* (*to be done*) full logging of a communication session
* (*to be done*) replay step-by-step of a session for deep analysis

## Setup & Utilisation
All the information is in the [Wiki](https://github.com/Overdrivr/Telemetry/wiki).
