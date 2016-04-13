[![Join the chat at  https://gitter.im/Overdrivr/pytelemetry](https://badges.gitter.im/Overdrivr/pytelemetry.svg)](https://gitter.im/Overdrivr/pytelemetry?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Stories in Ready](https://badge.waffle.io/Overdrivr/pytelemetrycli.svg?label=ready&title=Ready)](http://waffle.io/Overdrivr/pytelemetrycli)
[![Build status](https://ci.appveyor.com/api/projects/status/bglm8olo8kp8x1wr?svg=true)](https://ci.appveyor.com/project/Overdrivr/telemetry)

`Current status` *Active developement. API should remain globally stable. Test coverage decent. Need improvements to ease external contributions.*

## Overview
`Telemetry` enables easy communication and data visualization between a computer and any embedded platform, like `ARM Mbed` or `Arduino`.

Specifically, `Telemetry` is a communication protocol, implemented in C language.

![Overview](https://raw.githubusercontent.com/Overdrivr/Telemetry/master/pubsub_overview.png)

Data is exchanged on named channels, called *topics* (ex : `foo`, `bar` and `qux` on the figure above).

Sending data is called *publishing*.

```cpp
Telemetry TM;
int32_t i = 123;

TM.pub_i32("foo", i);
```

Receiving data is called *subscribing*. Basically, `Telemetry` lets you attach variables and functions to topics.
When fresh data is received under a topic, attached variables will be updated and attached functions will be called.

```cpp
Telemetry TM;
float throttle;

TM.attach_f32_to("throttle", &throttle);

for(;;) {
  TM.update();
}
```

# Data visualization

As soon as you start publishing, you can enjoy on your computer powerful data visualization using the
[Pytelemetry Command Line Interface](https://github.com/Overdrivr/pytelemetrycli)
[![PyPI version](https://badge.fury.io/py/pytelemetrycli.svg)](https://badge.fury.io/py/pytelemetrycli).

The CLI is a python package that can be installed with `pip`, and runs on Windows, Mac OS and Linux.

Directly in a terminal, with a few commands, you can :
* list all received topics
* print samples from a given topic
* publish data on a topic
* open high-performance graphs that plots data from the device in real-time
* full logging of a communication session
* (*to be done*) replay step-by-step of a session for deep analysis

![Console example](https://raw.githubusercontent.com/Overdrivr/pytelemetrycli/master/console.png)

![Plot example](https://raw.githubusercontent.com/Overdrivr/pytelemetrycli/master/graph.png)


## Central documentation

* [Overview of the library](https://github.com/Overdrivr/Telemetry/wiki/Overview)
* [Protocol description](https://github.com/Overdrivr/Telemetry/wiki/Protocol-description)
* [A non-exhaustive list of all the awesome features](https://github.com/Overdrivr/Telemetry/wiki/Awesome-features-overview)

All the information can be found from the [Wiki Home](https://github.com/Overdrivr/Telemetry/wiki).

## Motivation

This tool was designed with five objectives in mind.

* **Fast prototyping and debugging**. Set everything up in a few minutes and start debugging any embedded device efficiently. Forget about printf. Forever.
* **Communication-based applications**. Stop re-writing custom protocols for each new project.
* **Remote update of parameters**. Tune your embedded application without loosing time compiling & flashing just for parameter tuning.
* **Data plotting**. Plot data from the device in no time. Standard linear data is supported, but also arrays, sparse arrays. In the future, also Matrices, XYZ, and RGB-type codes.
* **Reusability**. The protocol is highly flexible, loosely coupled to your application. It can be used in a wide number of application scenarios.

*todo: list of alternatives*

## Protocol implementation in python [![PyPI version](https://badge.fury.io/py/pytelemetry.svg)](https://badge.fury.io/py/pytelemetry)

[`pytelemetry`](https://github.com/Overdrivr/pytelemetry) is the python equivalent of this protocol, and is 100% compatible.
You can use it (without the CLI) to write simple python scripts that communicate with the device, to send commands and update parameters in real time.
It is highly suitable for remote control of robots, RC cars, etc.  
