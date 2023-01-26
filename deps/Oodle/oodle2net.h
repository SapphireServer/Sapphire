#ifndef __OODLE2NET_H__
#define __OODLE2NET_H__
#include <stdint.h>

extern "C" intptr_t  OodleNetwork1_Shared_Size( int32_t htbits );

extern "C" intptr_t  OodleNetwork1UDP_State_Size();

extern "C" void  OodleNetwork1_Shared_SetWindow(
  void* shared,
  int32_t htbits,
  const void* window,
  int32_t windowSize
);

extern "C" void OodleNetwork1UDP_Train(
  void* state,
  const void* shared,
  const void** trainingPacketPointers,
  const int32_t* trainingPacketSizes,
  int32_t numTrainingPackets
);

extern "C" bool OodleNetwork1UDP_Decode(
  void* state,
  const void* shared,
  const void* enc,
  intptr_t encSize,
  void* dec,
  intptr_t decSize
);

#endif