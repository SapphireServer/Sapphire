#ifndef SAPPHIRE_LGBTYPES_H
#define SAPPHIRE_LGBTYPES_H

#include "vec3.h"
#include "DatCategories/DatCommon.h"
#include "DatCategories/InstanceObject.h"




struct BgPartsData : public InstanceObject
{
  int32_t AssetPath;
  int32_t CollisionAssetPath;
  eModelConfigCollisionType CollisionType;
  uint32_t AttributeMask;
  uint32_t Attribute;
  int32_t CollisionConfig;
  int8_t IsVisible;
  uint8_t RenderShadowEnabled;
  uint8_t RenderLightShadowEnabled;
  uint8_t Padding00[1];
  float RenderModelClipRange;
};







struct CollisionBoxInstanceObject : public InstanceObject
{
  TriggerBoxInstanceObject triggerBox;
  uint32_t m_attribute;
  uint32_t m_attributeMask;
  uint32_t m_resourceId;
  bool m_pushPlayerOut;
};

#endif //SAPPHIRE_LGBTYPES_H
