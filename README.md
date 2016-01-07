## Purpose
Telemetry is a point-to-point data-exchange protocol, suitable for master/slave applications.

The library based on the publish/subscribe mechanism compatible with any packet-based transport protocol.

It can be used to read telemetry and write parameters from a computer on an embedded device over a serial port.

Written in C language, the library is multi-platform and follows C89 standard. Thus it is compatible with a wide range of platforms.

## Why this library
Reading telemetry and configuring remotely a device is useful during embedded applications development, for debugging, or simply required by the final application.


## Usage
### publish

Messages can be published to a topic identified by a string.

```c
float readOnlyVar = 0;

// Sends a message containing a value to topic 'foo'
publish("foo",readOnlyVar);
// Sends a message containing a string to topic 'foo'
publish("foo","variable foo sent.");
```

### subscribe to a topic

Subscribe a callback to a topic to be notified when a new message is received.

```c
// Callbacks must follow this construct
void callback(state* s, message m)
{
  // Check message is of expected type
  if(m->type == type::float32){
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

### state

The state is defined by you, the user, and provided to Telemetry during initialization. It is made available to each subscribed event by being passed as first callback parameter.
The state can be seen as a shared-space where you can put writeable parameters in order to access them later.

```c
struct state {
    float someParam;
    int32_t someOtherParam;
};

initTelemetry(&state);
```

## Set-up
Telemetry can be setup in different manners, depending if you are targeting a desktop or embedded application.

### Desktop application
#### Work with headers / binaries
For desktop applications, you just need a regular C compiler with its `/bin` subfolder accessible OS-wide.
On windows this means you must add `/bin` to the PATH.

Then, with a console pointing to the project root directory
```bash
gradlew assembleDebugMainExecutable ?
```
to compile in debug mode or

```bash
gradlew assembleReleaseMainExecutable ?
```
to compile in release mode.

#### Work directly from files
The other option is to add the `scr/telemetry` folder to your project. This task is IDE-dependent, some IDE specific rules may apply.

### Embedded devices
For embedded devices, the only option is to the `src/telemetry` folder to your project.

#### Note on supported devices
...

## Testing
Testing is performed on a computer, by running the following gradle task.

```bash
gradlew test
```

## History
Successor of DistantIO.
Freely inspired on MQTT.
