## Purpose
Telemetry is a point-to-point data-exchange library. Its goal is to facilitate exchange of (wait for it...) telemetry and remote control.
It is suitable for master/slave applications or device-to-device intercommunication.

The library is using the publish/subscribe mechanism.

Written in ANSI C language, the library is multi-platform and compatible with a wide range of embedded platforms.

## Why this library
Reading telemetry and configuring remotely a device is useful during embedded applications development, for debugging, or simply required by the final application.


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

Subscribe a callback to a topic to be notified when a new message is received.

```c
// Callbacks must follow this construct
void callback(TM_state* s, TM_msg* m)
{
  // Check message is of expected type
  if(m->type == TM_type_float32){
    // Then put the received message (a float value here) into a variable
    float v;
    if(emplace(m, &v))
    {
      // v now contains the received value
    }
  }
}

subscribe("foo", callback);
```

The `TM_state` data structure (refered after as the state) must be defined by you, the user, and provided to Telemetry during initialization.
Telemetry will not in any way make changes to the state.
The state can be seen as a storage space where you can place writeable parameters.
It is passed to each subscribed callback, allowing you to easily access it without needing global variables.

```c
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
Simply add the `scr/telemetry` folder to your project.\
Please note that some `#include` directives might become broken in the process, because of the way gradle abstracts the folder hierarchy.


#### Note on supported devices
...

## Testing
Testing is performed on a computer, by running the following gradle task.

```bash
gradlew installDebugTestsExecutable
```

Then

```bash
cd build/install/testsExecutable/debug
tests.bat
```

## History
Successor of DistantIO.
Freely inspired on MQTT.
