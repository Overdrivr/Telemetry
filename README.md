## Purpose
Telemetry is a point-to-point data-exchange library. Its goal is to facilitate exchange of (wait for it...) telemetry and remote control.
It is suitable for master/slave or device-to-device intercommunication.

The library is using a publish/subscribe mechanism.

Written in ANSI C language, the library is multi-platform and compatible with a wide range of embedded platforms.

## Why this library ?
This library aims at providing a straightforward way to read telemetry and configure remotely an embedded device.
It can prove useful during embedded applications development, for debugging or for final application.
It is designed to be easy to use and easy to test.

## Usage
### publish on a topic

Messages can be published to a topic identified by a string.

```c
float readOnlyVar = 0;

// Sends a message containing a float32 value on the topic 'foo'
publish_f32("foo",readOnlyVar);
// Sends a message containing a string on the topic 'foo'
publish("foo","variable foo sent.");
```

### subscribe to a topic

Subscribe a callback to be notified when a new message is received.

```c
// Callbacks must follow this construct
void callback(TM_state* s, TM_msg* m)
{
  // Perform action on topic
  if(strequal(strm->topic,"foo"))
  {

  }

  // Perform action on message type
  if(m->type == TM_type_float32)
  {
    // Store the received binary data (a float value here) into a variable
    float v;
    if(emplace(m, &v))
    {
      // v now contains the received value
    }
  }
}

// ..
subscribe(callback);
```

The `TM_state` data structure is a user-storage space that is defined the user.
It must be provided to Telemetry during initialization.
Telemetry will not in any way make changes to the state.
The state can be primarily to store writeable parameters.
It is passed to the subscribed callback, allowing you to easily access it without needing global variables.

```c
// Some random user-defined fields in TM_state
struct TM_state {
    float someParam;
    int32_t someOtherParam;
};

// No need to typedef it, it is forward-defined in telemetry.h

TM_state state;

initTelemetry(&state);
```

## Set-up
Telemetry can be setup in different manners, depending if you are targeting a desktop or embedded application.

### Build with gradle

For desktop applications, you just need a regular C compiler with its `/bin` subfolder accessible OS-wide.
On windows this means you must add `/bin` to the PATH.

Then, with a console pointing to the project root directory
```bash
gradlew build
```

#### Work directly from files
For embedded devices, or if you do not wish to use the gradle build system, you can work directly from files.
Add the following folders to your project :
```
scr/telemetry
src/framing
src/crc16
src/huffman
```
Please note that some `#include` directives may become broken in the process, because of the way gradle abstracts the folder hierarchy.
You will need to fix them manually since it depends on your build setup.

#### Note on supported devices
...

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
Successor of DistantIO.
Freely inspired on MQTT.
