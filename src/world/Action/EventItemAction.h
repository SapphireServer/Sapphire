#pragma once

#include "Action.h"
#include <Exd/ExdDataGenerated.h>

namespace Sapphire::Data
{
  struct EventItem;
  using EventItemPtr = std::shared_ptr< EventItem >;
}

namespace Sapphire::World::Action
{
  class EventItemAction : public Action
  {
  public:
    EventItemAction( Entity::CharaPtr source, uint32_t eventItemId, Data::EventItemPtr itemActionData,
                     uint32_t sequence, uint64_t targetId );

    virtual ~EventItemAction() = default;

    bool init();

    void execute() override;

    void start() override;


  private:
    Data::EventItemPtr m_eventItemAction;
    uint32_t m_eventItem;
    uint32_t m_sequence;
  };
}