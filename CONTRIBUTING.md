# Contributing

We love pull requests from everyone. If you wish to contribute, here is how to do it.

If you wish to contribute in any way, first make sure a ticket is open.
The goal is to make sure before you dive into the code that potential changes conform to the goals of the project.
You can either create a ticket or propose on an existing one to take care of it.

Then, fork the repository and clone it onto your machine.

```
git clone git@github.com:your-username/Telemetry.git
```

# Project structure

This project is composed of two parts.

* Core library : located inside the `./src` folder, it is pure C code, not tied to any platform.
* Distributions  : assembled from `./configs`, `./drivers`, `./interfaces` and `./version` and the core lirary.
Each distribution contains platform-specific code.

The interfaces provide a unified way of interacting with Telemetry no matter the platform.
Interfaces are implemented in a header file, and are a collection of functions or a class defining a set of methods.
Currently, there are two different interfaces for the project:
* C
* C++

Mbed and Arduino are using the C++ interface.

Each distribution needs to use one or the other.

# Core library contributions

Inside the project folder, compile the core library and run the tests :

```shell
gradlew installTestsDebugExecutable
cd ./build/install/tests/debug/
tests.bat
```

Make the appropriated changes, add new tests to ensure your additions are running smoothly.

Build and test again. If everything goes well, propose a pull request.

Your changes will be tested automatically on both continuous integration servers.
You can check the tests status on your pull request page.

At this point, your pull request will be reviewed.
Either it will be accepted, or you will receive some feedback before it can be accepted.

# Distributions contribution

## Modify and existing one

to be done

## Create a new distribution

to be done
