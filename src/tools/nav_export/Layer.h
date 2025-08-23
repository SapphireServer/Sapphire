#pragma once
#include <stdint.h>


struct LayerGroup
{
  uint32_t LayerGroupID;
  int32_t Name;
  int32_t Layers;
  int32_t Layer_Count;
};

struct Layer
{
  uint32_t LayerID;
  int32_t Name;
  int32_t InstanceObjects;
  int32_t InstanceObject_Count;
  int8_t ToolModeVisible;
  int8_t ToolModeReadOnly;
  int8_t IsBushLayer;
  int8_t PS3Visible;
  int32_t LayerSetRef;
  uint16_t FestivalID;
  uint16_t FestivalPhaseID;
  int8_t IsTemporary;
  int8_t IsHousing;
  uint16_t VersionMask;
  uint32_t Reserved;
  int32_t OBSetReferencedList;
  int32_t OBSetReferencedList_Count;
  int32_t OBSetEnableReferencedList;
  int32_t OBSetEnableReferencedList_Count;
};