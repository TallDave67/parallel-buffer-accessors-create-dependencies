# Parallel: Buffer Accessors Create Data Dependencies (DPC++)

Using Intel's oneAPI DPC++.  The order in which you submit kernels to a queue and the buffer accessors created for those kernels will imply data dependencies between the kernels that will be used to generate the SYCL graph of kernel execution order.

Linux distro "Pop!_OS 21.04"

cmake version 3.18.4

Intel(R) oneAPI DPC++/C++ Compiler 2021.3.0 (2021.3.0.20210619)

## Steps

*I placed this in my .bashrc file so the dpcpp compiler can be found.*

> *export ONEAPI_DIR="/opt/intel/oneapi"*

> *[ -s "$ONEAPI_DIR/setvars.sh" ] && \. "$ONEAPI_DIR/setvars.sh"  # initialize oneAPI environment*

cd oneapi

./build.sh

./build/buffer-accessors-create-dependencies.cpp

## History

dates: July 16 & 21, 2021

duration: 4 hours

### Code from Another Developer

This code came directly from Intel.

[oneAPI Base Training Module 2: DPC++ Program Structure](https://devcloud.intel.com/oneapi/get_started/baseTrainingModules/)

I modified the original Intel code to display more readable output.

### SYCL Execution Graph

![Alt](/SYCL_dependency_graph.png "Execution Order")

## Output

[Output](https://github.com/TallDave67/parallel-buffer-accessors-create-dependencies/blob/main/oneapi/output.txt)
