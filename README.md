# Async C++ JSON API Client

## Build and test

Install the building tools

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake lcov python3-pip
sudo pip3 install setuptools pre-commit
```

Install the dependencies:

```bash
sudo apt-get update
sudo apt-get install -y libboost1.58-all-dev libfltk1.3-dev libjsoncpp-dev
```

Install pre-commit

```bash
pre-commit install
```

Build the project

```bash
cmake .
cmake --build .
```

Run the tests

```bash
make test
# or
make CTEST_OUTPUT_ON_FAILURE=1 test
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

Linting Checks

```bash
make apiclient_lint
```

## Colaborate

Please follow the style guide:
https://google.github.io/styleguide/cppguide.html

## Usage
