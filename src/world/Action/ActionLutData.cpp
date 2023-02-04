#include "ActionLut.h"
#include "ActionLutData.h"
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace Sapphire;
using namespace Sapphire::World::Action;
namespace fs = std::filesystem;

ActionLut::Lut ActionLut::m_actionLut;

std::unordered_map< std::string, Common::ParamModifier > ActionLutData::m_modifierStringMap =
{
  { "Strength", Common::ParamModifier::Strength },
  { "Dexterity", Common::ParamModifier::Dexterity },
  { "Vitality", Common::ParamModifier::Vitality },
  { "Intelligence", Common::ParamModifier::Intelligence },
  { "Mind", Common::ParamModifier::Mind },
  { "Piety", Common::ParamModifier::Piety },
  { "HP", Common::ParamModifier::HP },
  { "MP", Common::ParamModifier::MP },
  { "TP", Common::ParamModifier::TP },
  { "GP", Common::ParamModifier::GP },
  { "CP", Common::ParamModifier::CP },
  { "PhysicalDamage", Common::ParamModifier::PhysicalDamage },
  { "MagicDamage", Common::ParamModifier::MagicDamage },
  { "Delay", Common::ParamModifier::Delay },
  { "AdditionalEffect", Common::ParamModifier::AdditionalEffect },
  { "AttackSpeed", Common::ParamModifier::AttackSpeed },
  { "BlockRate", Common::ParamModifier::BlockRate },
  { "BlockStrength", Common::ParamModifier::BlockStrength },
  { "Parry", Common::ParamModifier::Parry },
  { "AttackPower", Common::ParamModifier::AttackPower },
  { "Defense", Common::ParamModifier::Defense },
  { "Accuracy", Common::ParamModifier::Accuracy },
  { "Evasion", Common::ParamModifier::Evasion },
  { "MagicDefense", Common::ParamModifier::MagicDefense },
  { "CriticalHitPower", Common::ParamModifier::CriticalHitPower },
  { "CriticalHitResilience", Common::ParamModifier::CriticalHitResilience },
  { "CriticalHit", Common::ParamModifier::CriticalHit },
  { "CriticalHitEvasion", Common::ParamModifier::CriticalHitEvasion },
  { "SlashingResistance", Common::ParamModifier::SlashingResistance },
  { "PiercingResistance", Common::ParamModifier::PiercingResistance },
  { "BluntResistance", Common::ParamModifier::BluntResistance },
  { "ProjectileResistance", Common::ParamModifier::ProjectileResistance },
  { "AttackMagicPotency", Common::ParamModifier::AttackMagicPotency },
  { "HealingMagicPotency", Common::ParamModifier::HealingMagicPotency },
  { "EnhancementMagicPotency", Common::ParamModifier::EnhancementMagicPotency },
  { "ElementalBonus", Common::ParamModifier::ElementalBonus },
  { "FireResistance", Common::ParamModifier::FireResistance },
  { "IceResistance", Common::ParamModifier::IceResistance },
  { "WindResistance", Common::ParamModifier::WindResistance },
  { "EarthResistance", Common::ParamModifier::EarthResistance },
  { "LightningResistance", Common::ParamModifier::LightningResistance },
  { "WaterResistance", Common::ParamModifier::WaterResistance },
  { "MagicResistance", Common::ParamModifier::MagicResistance },
  { "Determination", Common::ParamModifier::Determination },
  { "SkillSpeed", Common::ParamModifier::SkillSpeed },
  { "SpellSpeed", Common::ParamModifier::SpellSpeed },
  { "Haste", Common::ParamModifier::Haste },
  { "Morale", Common::ParamModifier::Morale },
  { "Enmity", Common::ParamModifier::Enmity },
  { "EnmityReduction", Common::ParamModifier::EnmityReduction },
  { "CarefulDesynthesis", Common::ParamModifier::CarefulDesynthesis },
  { "EXPBonus", Common::ParamModifier::EXPBonus },
  { "Regen", Common::ParamModifier::Regen },
  { "Refresh", Common::ParamModifier::Refresh },
  { "MainAttribute", Common::ParamModifier::MainAttribute },
  { "SecondaryAttribute", Common::ParamModifier::SecondaryAttribute },
  { "SlowResistance", Common::ParamModifier::SlowResistance },
  { "PetrificationResistance", Common::ParamModifier::PetrificationResistance },
  { "ParalysisResistance", Common::ParamModifier::ParalysisResistance },
  { "SilenceResistance", Common::ParamModifier::SilenceResistance },
  { "BlindResistance", Common::ParamModifier::BlindResistance },
  { "PoisonResistance", Common::ParamModifier::PoisonResistance },
  { "StunResistance", Common::ParamModifier::StunResistance },
  { "SleepResistance", Common::ParamModifier::SleepResistance },
  { "BindResistance", Common::ParamModifier::BindResistance },
  { "HeavyResistance", Common::ParamModifier::HeavyResistance },
  { "DoomResistance", Common::ParamModifier::DoomResistance },
  { "ReducedDurabilityLoss", Common::ParamModifier::ReducedDurabilityLoss },
  { "IncreasedSpiritbondGain", Common::ParamModifier::IncreasedSpiritbondGain },
  { "Craftsmanship", Common::ParamModifier::Craftsmanship },
  { "Control", Common::ParamModifier::Control },
  { "Gathering", Common::ParamModifier::Gathering },
  { "Perception", Common::ParamModifier::Perception },
  { "HPPercent", Common::ParamModifier::HPPercent },
  { "MPPercent", Common::ParamModifier::MPPercent },
  { "TPPercent", Common::ParamModifier::TPPercent },
  { "GPPercent", Common::ParamModifier::GPPercent },
  { "CPPercent", Common::ParamModifier::CPPercent },
  { "PhysicalDamagePercent", Common::ParamModifier::PhysicalDamagePercent },
  { "MagicDamagePercent", Common::ParamModifier::MagicDamagePercent },
  { "AttackPowerPercent", Common::ParamModifier::AttackPowerPercent },
  { "DefensePercent", Common::ParamModifier::DefensePercent },
  { "AccuracyPercent", Common::ParamModifier::AccuracyPercent },
  { "EvasionPercent", Common::ParamModifier::EvasionPercent },
  { "MagicDefensePercent", Common::ParamModifier::MagicDefensePercent },
  { "CriticalHitPowerPercent", Common::ParamModifier::CriticalHitPowerPercent },
  { "CriticalHitResiliencePercent", Common::ParamModifier::CriticalHitResiliencePercent },
  { "CriticalHitPercent", Common::ParamModifier::CriticalHitPercent },
  { "EnmityPercent", Common::ParamModifier::EnmityPercent }
};

bool ActionLutData::cacheActions()
{
  std::fstream f;

  for( auto& p : fs::recursive_directory_iterator( "data/actions/" ) )
  {
    if( p.path().extension() == ".json" )
    {
      f.open( p.path() );

      if( !f.is_open() )
        return false;

      auto actionJSON = nlohmann::json::parse( f );

      for( auto& i : actionJSON.items() )
      {
        auto id = std::stoi( i.key() );
        auto action = i.value().get< ActionEntry >();
        ActionLut::m_actionLut.try_emplace( id, action );
      }

      f.close();
      f.clear();
    }
  }

  if( ActionLut::m_actionLut.empty() )
    return false;

  return true;
}

bool ActionLutData::reloadActions()
{
  if( !ActionLut::m_actionLut.empty() )
    ActionLut::m_actionLut.clear();

  return cacheActions();
}