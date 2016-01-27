## Purpose
Telemetry is a portable, fast, safe, and lightweight point-to-point data-exchange library.
It facilitates exchange of telemetry data and remote program control.
It is suitable for master/slave or device-to-device intercommunication and is fully compatible with embedded applications.
It can be used for real-time debugging and for end application.

## Operation
The library is using a publish/subscribe mechanism to transfer data on channels called 'topics'.

## Portability
Written in ANSI C language, the library is multi-platform and compatible with a wide range of desktop environment and embedded platforms.
It is not relying on any dynamic allocation schemes.
So far, the library has been tested on windows, ARM mbed (specifically on NXP platform Kinetis KL25Z).

## Usage

![publish subscribe concept](https://rawgit.com/Overdrivr/Telemetry/master/concept.svg)

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

// main()
// {
// ..

subscribe(callback);
// .. }

// your callback
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
Telemetry can be setup in different manners, depending if you are targeting a desktop or embedded application.

### Build with gradle

For desktop applications, you just need a regular C compiler with its `/bin` subfolder accessible OS-wide.
On windows this means you must add `/bin` to the PATH.
A quick way to check if the toolchain is well installed is to run
```bash
gcc -v
```

Then, with a console pointing to the project root directory you can build the project with a simple command
```bash
gradlew build
```

#### Work directly from files
For embedded devices, or if you do not wish to use the gradle build system, you can work directly from files.
Add the *contents* of the following folders in the same folder to your project :
```
scr/telemetry
src/framing
src/crc16
src/huffman
```

#### Note on supported devices
So far, the following embedded devices have been validated with it:
* NXP KL25Z

## Testing
Testing can be performed in a desktop environment, by running the following gradle tasks.

```bash
gradlew installDebugTestsExecutable
```

Then

```bash
cd build/install/testsExecutable/debug
tests.bat -v
```

## History
Successor of (DistantIO)[https://github.com/Overdrivr/DistantIO].
Freely inspired on MQTT.
