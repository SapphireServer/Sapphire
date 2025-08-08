#pragma once

#include "Action.h"
#include <Exd/Structs.h>

namespace Sapphire::Data
{
  struct ItemAction;
  using ItemActionPtr = std::shared_ptr< ItemAction >;
}

namespace Sapphire::World::Action
{
  class EventItemAction : public Action
  {
  public:
    EventItemAction( Entity::CharaPtr source, uint32_t eventItemId, std::shared_ptr< Excel::ExcelStruct< Excel::EventItem > > itemActionData,
                     uint32_t requestId, uint64_t targetId );

    EventItemAction( Entity::CharaPtr source, uint32_t eventItemId, std::shared_ptr< Excel::ExcelStruct< Excel::EventItem > > itemActionData,
                     uint32_t requestId, Common::FFXIVARR_POSITION3 pos, Common::CastType castType );

    virtual ~EventItemAction() = default;

    bool init();

    void execute() override;

    void onStart() override;


  private:
    std::shared_ptr< Excel::ExcelStruct< Excel::EventItem > > m_eventItemAction;
    uint32_t m_eventItem;
  };
}