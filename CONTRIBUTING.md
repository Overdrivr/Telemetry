# Contributing

We love pull requests from everyone. If you wish to contribute, here is how to do it.

You can contribute to Telemetry in two different aspects:
* Core library: the logic that powers the library
* Platform interfaces: Convenient *batteries-included* wrappers of Telemetry for platforms like Arduino, ARM mbed, etc.

If you wish to contribute to the core library, make sure to open a ticket first to propose your ide.
The goal is to validate proposed changes before you dive into the code.

Then, fork the repository and clone it onto your machine.

```
git clone git@github.com:your-username/Telemetry.git
```

Make the changes, then open a Pull Request.

If you wish to contribute to an existing Telemetry wrapper for Arduino or Mbed,
see their respective repositories for contribution:
* [Telemetry-arduino](https://github.com/Overdrivr/Telemetry-arduino)
* [Telemetry-mbed](https://github.com/Overdrivr/Telemetry-mbed)

If you wish to implement a new platform, feel free to create a new repository
yourself if you intend to maintain it yourself, or open a ticket to gracefully ask for it.

# Core library contributions

Inside the project folder, compile the core library and run the tests :

```shell
gradlew installTestDebugExecutable
cd ./build/install/test/debug/
test.bat
```

Make the appropriated changes, add new tests to ensure your additions are running smoothly.

Build and test again. If everything goes well, propose a pull request.

Your changes will be tested automatically on both continuous integration servers.
You can check the tests status on your pull request page.

At this point, your pull request will be reviewed.
Either it will be accepted, or you will receive some feedback before it can be accepted.
