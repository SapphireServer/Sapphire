#ifndef _CALCSTATS_H
#define _CALCSTATS_H

#include <Common.h>
#include "Forwards.h"

namespace Sapphire::Math
{

  class CalcStats
  {
  public:
    static const uint32_t AUTO_ATTACK_POTENCY = 110;
    static const uint32_t RANGED_AUTO_ATTACK_POTENCY = 100;

    static float calculateBaseStat( const Entity::Chara& chara );

    static uint32_t calculateMaxHp( Sapphire::Entity::PlayerPtr pPlayer, FrameworkPtr pFw  );

    /*!
     * @brief Calculates the probability of a block happening
     */
    static float blockProbability( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the probability of a direct hit happening
     */
    static float directHitProbability( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the probability of a critical hit happening
     */
    static float criticalHitProbability( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the contribution of potency to damage output.
     *
     * @param potency The action potency
     */
    static float potency( uint16_t potency );

    static float autoAttackPotency( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Weapon damage is the contribution the weapon's damage rating
     *
     * @param chara The source/casting character.
     * @param weaponDamage the weapons physical or magic damage
     */
    static float weaponDamage( const Sapphire::Entity::Chara& chara, float weaponDamage );

    /*!
     * @brief Calculates the contribution of attack power to damage dealt with consideration for the primary stat
     * @todo Only works at level 70
     *
     * @param chara The source/casting character.
     */
    static float getPrimaryAttackPower( const Sapphire::Entity::Chara& chara );

    static float attackPower( const Sapphire::Entity::Chara& chara );

    static float magicAttackPower( const Sapphire::Entity::Chara& chara );

    static float healingMagicPower( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates determinations contribution to damage and healing output.
     *
     * @param chara The source/casting character.
     * @return Returns a rational number rounded to 3 decimal places.
     */
    static float determination( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the tenacity contribution to damage, mitigation and healing.
     *
     * @param chara The source/casting character.
     * @return Returns a rational number rounded to 3 decimal places.
     */
    static float tenacity( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the bonus granted by either spell speed or skill speed depending on the casters classjob.
     *
     * @param chara The source/casting character.
     */
    static float speed( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the amount of bonus damaged applied on a critical hit
     * @note Called Critical Hit Rate in the TJ document but I think that name is a bit too ambiguous - f(CHR)
     *
     * @param chara The source/casting character.
     */
    static float criticalHitBonus( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates how much damage you mitigate via physical defence
     *
     * @param chara The source/casting character.
     */
    static float physicalDefence( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates how much damage you mitigate via magical defence
     *
     * @param chara The source/casting character.
     */
    static float magicDefence( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the percentage of damage that is mitigated on a successful block
     *
     * @param chara The source/casting character.
     */
    static float blockStrength( const Sapphire::Entity::Chara& chara );

    static float autoAttack( const Sapphire::Entity::Chara& chara );

    /*!
     * @brief Calculates the multiplier that healing magic potency affects healing output
     *
     * @todo Only works for level 70
     *
     * @param chara The source/casting character.
     */
    static float healingMagicPotency( const Sapphire::Entity::Chara& chara );

    ////////////////////////////////////////////

    static float calcAutoAttackDamage( const Sapphire::Entity::Chara& chara );

    static float calcActionDamage( const Sapphire::Entity::Chara& chara, uint32_t ptc, float wepDmg );

    static uint32_t primaryStatValue( const Sapphire::Entity::Chara& chara );
  private:

    /*!
     * @brief Has the main attack power calculation allowing for de-duplication of functions.
     *
     * @param attackPower The magic/physical attack power value.
     */
    static float calcAttackPower( const Sapphire::Entity::Chara& chara, uint32_t attackPower );


  };

}

#endif
