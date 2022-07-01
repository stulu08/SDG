#pragma once

#pragma warning(disable:4251)

#include "CoreConfig.h"
#include "PlatformConfig.h"

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <string>

#define ST_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define ST_BIT(x) (1 << x)
#define ST_CONCAT_INNER(a, b) a ## b
#define ST_CONCAT(a, b) ST_CONCAT_INNER(a, b)


namespace SDG {
	template<typename T>
	using Scope = STULU_API std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> createScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	template<typename T>
	using Ref = STULU_API std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}