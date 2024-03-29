#pragma once

#include "type.h"

namespace FVK::Internal {
	inline FU::Log::Messenger GMessenger{};
}

namespace FVK {
	using MessengerCallbackType = void(*)(const std::string&);
}