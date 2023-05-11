#ifndef __OODLE2NET_H__
#define __OODLE2NET_H__

extern "C" intptr_t __stdcall OodleNetwork1_Shared_Size( int32_t htbits );

extern "C" intptr_t __stdcall OodleNetwork1UDP_State_Size();
extern "C" intptr_t __stdcall OodleNetwork1TCP_State_Size();

extern "C" void __stdcall OodleNetwork1_Shared_SetWindow(
  void* shared,
  int32_t htbits,
  const void* window,
  int32_t windowSize
);

extern "C" void __stdcall OodleNetwork1UDP_Train(
  void* state,
  const void* shared,
  const void** trainingPacketPointers,
  const int32_t* trainingPacketSizes,
  int32_t numTrainingPackets
);

extern "C" void __stdcall OodleNetwork1TCP_Train(
  void* state,
  const void* shared,
  const void** trainingPacketPointers,
  const int32_t* trainingPacketSizes,
  int32_t numTrainingPackets
);

extern "C" bool __stdcall OodleNetwork1UDP_Decode(
  void* state,
  const void* shared,
  const void* enc,
  intptr_t encSize,
  void* dec,
  intptr_t decSize
);

extern "C" bool __stdcall OodleNetwork1TCP_Decode(
  void* state,
  const void* shared,
  const void* enc,
  intptr_t encSize,
  void* dec,
  intptr_t decSize
);

extern "C" intptr_t __stdcall OodleNetwork1UDP_Encode(
  void* state,
  const void* shared,
  const void* dec,
  intptr_t decSize,
  void* enc
);

extern "C" intptr_t __stdcall OodleNetwork1TCP_Encode(
  void* state,
  const void* shared,
  const void* dec,
  intptr_t decSize,
  void* enc
);

#endif