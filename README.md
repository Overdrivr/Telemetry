[![Stories in Ready](https://badge.waffle.io/Overdrivr/pytelemetrycli.svg?label=ready&title=Ready)](http://waffle.io/Overdrivr/pytelemetrycli)
## Overview
Telemetry is a lightweight, portable, fast and error-resilient point-to-point protocol. It is implemented in C language.

Ultimately, `Telemetry` helps you achieve effortless communication between a computer and an embedded device, with a minimal amount of code.

![Overview](https://raw.githubusercontent.com/Overdrivr/pytelemetrycli/master/overview.png)


* [`pytelemetry`](https://github.com/Overdrivr/pytelemetry)
[![PyPI version](https://badge.fury.io/py/pytelemetry.svg)](https://badge.fury.io/py/pytelemetry) is the python implementation of this protocol, and lets you write simple python scripts that communicate with a device.

* [`pytelemetrycli`](https://github.com/Overdrivr/pytelemetrycli)[![PyPI version](https://badge.fury.io/py/pytelemetrycli.svg)](https://badge.fury.io/py/pytelemetrycli) is an awesome command line interface that allows you to communicate directly with your device, write data from your computer, open high-performance graphs that plots data from the device in real-time. All of that accessible by typing a few commands.

## Why using it ?

Telemetry is for you if :

* you are using `printf` to debug your embedded application
* you are constantly re-writing custom protocols on top of the serial port
* you need a **reliable** and **error-tolerant** communication protocol
* you want to finely tune your application without loosing time compiling & flashing just to tune a parameter
* you want to **plot** parameters of your application in **real-time**
* your embedded device has very limited resources and will tolerate only a lightweight communication library

## Principle
The underlying communication protocol mostly follows the [PubSub](https://en.wikipedia.org/wiki/Publish%E2%80%93subscribe_pattern) (Publish/Subscribe) messaging pattern.

> [..] messages are published to "topics" or named logical channels. Subscribers in a topic-based system will receive all messages published to
> the topics to which they subscribe [..].
> *Source: Wikipedia*

## Portability
Written in standard C language, the library is multi-platform and compatible with a wide range of desktop environment and embedded platforms.
It is not relying on any dynamic allocation schemes.
So far, the library has run successfully on desktop and ARM mbed (specifically on NXP platform Kinetis KL25Z).
Adding a new platform is straightforward ; it takes 4 lines of codes if you already have a decent buffered UART library on it (which is often the case).

## Usage


### publish on a topic

Messages can be published to a topic identified by a string.

```c
float readOnlyVar = 1.23E4;

// Sends a message containing a float32 value on the topic 'foo'
publish_f32("foo",readOnlyVar);
// Sends a message containing a string on the topic 'foo'
publish("foo","variable foo sent.");
```

### subscribe to a topic

Subscribe a callback to be notified when a new message is received.

```c

void main()
{
   // ..

   subscribe(callback);
   // ..
   while(1)
   {
     update_telemetry();
   }
}

// This callback function will be called, from update_telemetry(), every time you receive a new frame
void callback(TM_state* s, TM_msg* m)
{
  // Perform action on message type
  if(m->type == TM_type_float32)
  {
    float v;
    emplace_f32(m, &v))// v now contains the received value
  }
}

```
## Set-up
Telemetry can be setup in different manners, depending if you are targeting a desktop build (for running the test suite) or an embedded application.

### Embedded devices
For embedded devices, simply add the *contents* of the following folders in the same folder to your project :
```
scr/telemetry
src/framing
src/crc16
src/huffman
```
Then, you can start using all methods defined in `src\telemetry\headers\telemetry.h` (*Note: documentation is in process*)

### Desktop

For desktop applications, there are two requirements to build the project using [Gradle]("http://gradle.org/").

1. You need a GCC compatible toolchain with its `/bin` subfolder accessible OS-wide.
On Windows you must install a GCC toolchain. I personnally use [TDM-GCC](http://tdm-gcc.tdragon.net/).
If not done during the installation, you must add the toolchain's `/bin` subfolder to the PATH environment variable.

On Mac and Unix, GCC toolchain is usually always present by default and I believe you have nothing to do.

For all systems, a quick way to check if the toolchain is well installed

```bash
gcc -v
```
If it displays a bunch of version messages and doesn't throw an error, you're good.

2. Install [java](https://www.java.com/fr/)  (required by Gradle)

Then, once it's done, you can start building the project.

With a terminal pointing to the project root directory :

```bash
gradlew build
```
To run the tests

```bash
gradlew installTestsReleaseExecutable
build\install\tests\release\tests.bat -v
```

#### Note on supported devices
So far, the following embedded devices have been validated with it:
* NXP KL25Z

## History
Successor of (DistantIO)[https://github.com/Overdrivr/DistantIO].
Freely inspired on MQTT.
