#pragma once

#include "Action.h"
#include <Exd/Structs.h>

namespace Sapphire::World::Action
{
  class MountAction : public Action
  {
  public:
    MountAction( Entity::CharaPtr source, uint16_t mountId, uint16_t sequence,
                 std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData );
    virtual ~MountAction() = default;

    bool preCheck() override;

    void start() override;

    void execute() override;

  private:
    uint16_t m_mountId;
  };
}