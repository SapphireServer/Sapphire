#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <mutex>

// Export macro for the common library (Windows friendly)
#include <string>

namespace Sapphire::Common::detail
{
  // Returns a reference to the process-wide service slot for the given key name.
  // Backed by a process-wide shared section to ensure a single registry across modules.
  std::shared_ptr< void >& service_slot_by_name( const std::string& key ) noexcept;
}
