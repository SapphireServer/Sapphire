#ifndef SAPPHIRE_MOUNTACTION_H
#define SAPPHIRE_MOUNTACTION_H

#include "Action.h"

namespace Sapphire::World::Action
{
  class MountAction : public Action
  {
  public:
    MountAction( Entity::CharaPtr source, uint32_t mountId, uint16_t sequence, Data::ActionPtr actionData, FrameworkPtr fw );
    virtual ~MountAction() = default;

    bool preCheck() override;

    void start() override;

    void execute() override;

  private:
    uint32_t m_mountId;
  };
}

#endif //SAPPHIRE_MOUNTACTION_H
