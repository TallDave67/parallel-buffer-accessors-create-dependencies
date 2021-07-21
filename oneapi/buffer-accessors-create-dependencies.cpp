//==============================================================
// Copyright © 2020 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================

// The original Intel code has been modified by David Bellis in 2021

//==============================================================
// Copyright © 2020 Intel Corporation
//
// SPDX-License-Identifier: MIT
// =============================================================
#include <CL/sycl.hpp>

constexpr int num=16;
using namespace sycl;

void print_num(int num) {
  int _num = num;
  int spaces = 4;
  do
  {
    _num /= 10;
    --spaces;
  } while(_num != 0);
    
  while(spaces > 0)
  {
    --spaces;
    std::cout << " ";
  }
    
  std::cout << num;
}

int main() {
  auto R = range<1>{ num };
  //Create Buffers A and B
  buffer<int> A{ R }, B{ R };
      
  {
    std::cout << "before kernels have run" << std::endl;
    host_accessor readA(A,read_only);
    for (int i=0; i<num; ++i)
      print_num(readA[i]);
    std::cout << std::endl;

    host_accessor readB(B,read_only);
    for (int i=0; i<num; ++i)
      print_num(readB[i]);
    std::cout << std::endl;
  }
    
  //Create a device queue
  queue Q;

  //Submit Kernel 1
  Q.submit([&](handler& h) {
    //Accessor for buffer A
    accessor out(A,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      out[idx] = idx[0];
    }); 
  });

  //Submit Kernel 2
  Q.submit([&](handler& h) {
    //This task will wait till the first kernel is complete
    accessor out(A,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      out[idx] += idx[0];
    }); 
  });

  //Submit Kernel 3
  Q.submit([&](handler& h) { 
    //Accessor for Buffer B
    accessor out(B,h,write_only);
    h.parallel_for(R, [=](auto idx) {
      out[idx] = idx[0];
    }); 
  });

  //Submit task 4
  Q.submit([&](handler& h) {
    //This task will wait till kernel 2 and 3 are complete
    accessor in (A,h,read_only);
    accessor inout(B,h);
    h.parallel_for(R, [=](auto idx) {
      inout[idx] *= in[idx];
    }); 
  }); 
      
  // And the following is back to device code
  std::cout << "after kernels have run" << std::endl;
  host_accessor resultA(A,read_only);
  for (int i=0; i<num; ++i)
    print_num(resultA[i]);
  std::cout << std::endl;

  host_accessor resultB(B,read_only);
  for (int i=0; i<num; ++i)
    print_num(resultB[i]);
  std::cout << std::endl;
      
  return 0;
}
