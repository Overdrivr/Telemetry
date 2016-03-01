## commands recipe for regular build/test flow

Compiles telemetry core modules (`src/crc16`, `src/framing`, `src/telemetry`)
 in C, then C++, in debug mode.
Also compiles core tests and installs it to a dedicated folder.
```shell
gradlew installTestsDebugExecutable
```

Runs core tests
```shell
cd ./build/install/tests/debug/tests.bat
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

Generates the Mbed distribution by taking files inside `src/` `cpp_interface/`
and `drivers/`

```shell
gradlew distributeMbed
```

Compiles and installs in a folder mbedTest (integration tests) module.
```shell
gradlew installMbedTestDebug
gradlew moveTestVector
```

Runs Mbed integration tests
```shell
cd ./build/install/mbedTest/debug/
mbedTest.bat
cd ../../../../
```

If all tests passed, library can be released with good confidence.
