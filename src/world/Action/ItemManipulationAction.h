#pragma once

#include "Action.h"
#include <Exd/Structs.h>

namespace Sapphire::World::Action
{
  class ItemManipulationAction : public Action
  {
  public:
    ItemManipulationAction( Entity::CharaPtr source, uint32_t actionId, uint16_t requestId,
                  std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData, uint32_t delayTime );
    virtual ~ItemManipulationAction() = default;

    void start() override;

    void execute() override;

    bool update() override;

  private:
    void onFinish();

    uint32_t m_delayTimeMs{};
  };
}