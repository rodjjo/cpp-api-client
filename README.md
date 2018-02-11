# Async C++ JSNO API Client

## Build and test

Install the building tools

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake lcov
```

Install the dependencies:

```bash
sudo apt-get update
sudo apt-get install -y libboost1.58-all-dev libfltk1.3-dev libjsoncpp-dev
```

Build the project

```bash
cmake --build .
```

Run the tests

```bash
ctest
```

Coverage

```bash
cmake -DCMAKE_BUILD_TYPE=Debug .
make apiclient_coverage
```

Show coverage report

```bash
# you can replace firefox browser if you want to
firefox apiclient_coverage/index.html
```

## Usage
