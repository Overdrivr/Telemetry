[![Join the chat at  https://gitter.im/Overdrivr/pytelemetry](https://badges.gitter.im/Overdrivr/pytelemetry.svg)](https://gitter.im/Overdrivr/pytelemetry?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Stories in Ready](https://badge.waffle.io/Overdrivr/pytelemetrycli.svg?label=ready&title=Ready)](http://waffle.io/Overdrivr/pytelemetrycli)
[![Build status](https://ci.appveyor.com/api/projects/status/bglm8olo8kp8x1wr?svg=true)](https://ci.appveyor.com/project/Overdrivr/telemetry)
[![Documentation](https://readthedocs.org/projects/telemetry-docs/badge/?version=latest)](http://telemetry-docs.readthedocs.org/en/latest/)

`Current status` *Paused development for now, will restart once I find better ways of managing and distributing general-purpose embedded libraries. However, library is functional good stability & test coverage.*

### `announcement` We are launching [cronobo](https://cronobo.com)
> A new platform for interacting periodically with embedded devices, collecting their data and visualizing it. Feel free to check it out ! 

# Overview
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

For receiving data, `Telemetry` lets you attach variables and functions to topics.
When fresh data is received under a topic, attached variables will be updated and attached functions will be called.

```cpp
Telemetry TM;
float thr;

TM.attach_f32_to("throttle", &thr);

for(;;) {
  TM.update();
}
```

# Wrappers

Telemetry is written to be portable and general-purpose, and the core code is not tied to any hardware.

Wrappers for specific platforms are written to provide a plug-and-play manner to use Telemetry:
* [Arduino wrapper](https://github.com/Overdrivr/Telemetry-arduino)
* [Mbed wrapper](https://github.com/Overdrivr/Telemetry-mbed) (Available also on [Mbed repository](https://developer.mbed.org/users/Overdrivr/code/telemetry/) )
* Yotta (package manager) - in process

# Data visualization

As soon as a device publishes data, it is possible to leverage the power of
the [Pytelemetry Command Line Interface](https://github.com/Overdrivr/pytelemetrycli)
[![PyPI version](https://badge.fury.io/py/pytelemetrycli.svg)](https://badge.fury.io/py/pytelemetrycli).

This terminal application lets you interact with the device, using simple commands.

Opening a live plot is as simple as

```
:> plot someTopic
```

![Plot example](https://raw.githubusercontent.com/Overdrivr/pytelemetrycli/master/graph.png)


# Central documentation

* [Overview of the library](https://github.com/Overdrivr/Telemetry/wiki/Overview)
* [Protocol description](https://github.com/Overdrivr/Telemetry/wiki/Protocol-description)
* [A non-exhaustive list of all the awesome features](https://github.com/Overdrivr/Telemetry/wiki/Awesome-features-overview)

All the information can be found from the [Wiki Home](https://github.com/Overdrivr/Telemetry/wiki).
