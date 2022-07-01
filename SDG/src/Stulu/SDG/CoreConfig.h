#pragma once

#define ST_USE_OPENGL 1

#ifdef ST_USE_VULKAN
	#undef ST_USE_OPENGL
	define ST_USE_VULKAN 1
#endif 

#ifdef ST_DEBUG
	#define ST_SHOWCONSOLE 1

	#define	ST_ENABLE_TRACE_LOGGING 0

	#define ST_GRAPHICS_API_INFO_LOGGING 0 // GL_DEBUG_SEVERITY_LOW | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
	#define ST_GRAPHICS_API_VERBOSE_LOGGING 0 // GL_DEBUG_SEVERITY_NOTIFICATION | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
#elif ST_RELEASE
	#define ST_SHOWCONSOLE 1
#elif ST_DIST
	
#endif