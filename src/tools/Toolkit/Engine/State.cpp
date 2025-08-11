#include "State.h"

#include "Engine/GfxApi.h"
#include "Engine/Service.h"

using namespace Engine;

State::State( std::shared_ptr< ApplicationContext > pContext )
{
  m_context = std::move( pContext );
}

void State::onFinishState()
{
  m_bShouldFinish = true;
}