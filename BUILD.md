## commands recipe for regular build/test flow

Compiles telemetry core modules (`src/crc16`, `src/framing`, `src/telemetry`)
 in C, then C++, in debug mode.
Also compiles core tests and installs it to a dedicated folder.
```shell
gradlew installTestsDebugExecutable
```

Runs core tests
```shell
cd ./build/install/tests/debug/
tests.bat
cd ../../../../
```

Compiles test vectors (a collection of frames that serve as reference for
  integration tests) generator and installs it to a dedicated folder.

```shell
gradlew installTestVectorsGeneratorDebug
```

Runs test vectors generation
```shell
cd ./build/install/testVectorsGenerator/debug/
testVectorsGenerator.bat
cd ../../../../
```

Next steps can be performed for Mbed or Arduino distributions

## mbed distribution

Generates the Mbed distribution by taking files inside `src/` `cpp_interface/`
and `drivers/`

```shell
gradlew distributeMbed
```

Compiles and installs in a folder mbedTest (integration tests) module.
```shell
gradlew installMbedTestDebug
gradlew moveTestVectorMbed
```

Runs Mbed integration tests
```shell
cd ./build/install/mbedTest/debug/
mbedTest.bat
cd ../../../../
```

If all tests passed, mbed library can be released with good confidence.

```shell
gradle packMbed
```

This last command will generate an archive of the distribution inside
 `build/distributions/`

## arduino distribution

Generates the Arduino distribution by taking files inside `src/`,
`./cpp_interface/`, `./drivers/` and `./version/`

```shell
gradlew distributeArduino
```

Compiles and installs in a folder mbedTest (integration tests) module.
```shell
gradlew installArduinoTestDebug
gradlew moveTestVectorArduino
```

Runs Mbed integration tests
```shell
cd ./build/install/arduinoTest/debug/
arduinoTest.bat
cd ../../../../
```

If all tests passed, arduino library can be released with good confidence.

```shell
gradle packArduino
```

This last command will generate an archive of the distribution inside
 `build/distributions/`
