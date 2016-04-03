[![Join the chat at  https://gitter.im/Overdrivr/pytelemetry](https://badges.gitter.im/Overdrivr/pytelemetry.svg)](https://gitter.im/Overdrivr/pytelemetry?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Stories in Ready](https://badge.waffle.io/Overdrivr/pytelemetrycli.svg?label=ready&title=Ready)](http://waffle.io/Overdrivr/pytelemetrycli)
[![Twitter Follow](https://img.shields.io/twitter/follow/@remibgs.svg?style=social)](https://twitter.com/remibgs)
## Overview
`Telemetry` provides powerful communication and data visualization between a computer and any embedded device. This framework is fully compatible and supported on ARM Mbed and Arduino.

Telemetry is a lightweight, portable, fast and error-resilient point-to-point protocol. It is implemented in C language and Python (`Pytelemetry`).
![Overview](https://raw.githubusercontent.com/Overdrivr/Telemetry/master/pubsub_overview.png)

Data is exchanged on named channels, called *topics*. `foo`, `bar` and `qux` are all topics on the figure above.

`Telemetry` lets you attach your own C function to be notified each time a new frame is received. A collection of functions in the library can then help you update program parameters, or execute specific code when a specific topic is received, etc.

## Motivation

This tool was designed with five objectives in mind.

* **Fast prototyping and debugging**. Set everything up in a few minutes and start debugging any embedded device efficiently. Forget about printf. Forever.
* **Communication-based applications**. Stop re-writing custom protocols for each new project.
* **Remote update of parameters**. Tune your embedded application without loosing time compiling & flashing just for parameter tuning.
* **Data plotting**. Plot data from the device in no time. Standard linear data is supported, but also arrays, sparse arrays. In the future, also Matrices, XYZ, and RGB-type codes.
* **Reusability**. The protocol is highly flexible, loosely coupled to your application. It can be used in a wide number of application scenarios.

## Snippet - Arduino
Send an incrementing value on topic `count` and update variable **throttle** when receiving a new float value on topic `throttle`. Reset counter when throttle value is updated.

```c
#include <Telemetry.h>

Telemetry TM;
TM_state state;
int32_t i = 0;

struct TM_state {
  float throttle;
}

void refresh(TM_state * state, TM_msg * msg) {
    // If received topic is throttle, put new float value in state->throttle
    if(update_f32(msg,"throttle",&(state->throttle)))
      i = 0;
}

void setup() {
  TM.begin(9600);
  TM.subscribe(refresh, &state);
}

void loop() {
  TM.pub_i32("count",i++);
  delay(50);
}
```

## Python implementation [![PyPI version](https://badge.fury.io/py/pytelemetry.svg)](https://badge.fury.io/py/pytelemetry)

[`pytelemetry`](https://github.com/Overdrivr/pytelemetry) is the python equivalent of this protocol, and is 100% compatible.
You can use it to write simple python scripts that communicate with the device, to send commands and update parameters in real time.
It is highly suitable for remote control of robots, RC cars, etc.  

## The Command Line Interface [![PyPI version](https://badge.fury.io/py/pytelemetrycli.svg)](https://badge.fury.io/py/pytelemetrycli)

[`pytelemetrycli`](https://github.com/Overdrivr/pytelemetrycli) is an awesome command line interface that allows direct communication with the device and immediate data visualization.

Directly in a terminal, with a few commands, you can :
* list all received topics
* print samples from a given topic
* publish data on a topic
* open high-performance graphs that plots data from the device in real-time
* full logging of a communication session
* (*to be done*) replay step-by-step of a session for deep analysis

## Documentation

* [Overview of the library](https://github.com/Overdrivr/Telemetry/wiki/Overview)
* [Protocol description](https://github.com/Overdrivr/Telemetry/wiki/Protocol-description)
* [A non-exhaustive list of all the awesome features](https://github.com/Overdrivr/Telemetry/wiki/Awesome-features-overview)

All the information can be found from the [Wiki Home](https://github.com/Overdrivr/Telemetry/wiki).
