include "./vendor/premake/premake_customization/solution_items.lua"
include "./vendor/premake/premake_customization/generate_doc.lua"
workspace "SDG"
	startproject "SDG"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	flags
	{
		"MultiProcessorCompile"
	}
	solution_items 
	{
		"premake5.lua",
		"SDG/premake5.lua",
		"TestApp/premake5.lua",
		"README.md"
	}
	architecture "x86_64"

	filter "configurations:Debug"
		defines     "_DEBUG"

	filter "configurations:Release or Dist"
		defines     "NDEBUG"

	filter { "system:windows", "configurations:Dist", "toolset:not mingw" }
		flags		{ "LinkTimeOptimization" }

staticBuild = true
staticRuntime = true

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


vulkanSDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image"
IncludeDir["Vulkan"] = "%{vulkanSDK}/Include"

ProjectDir = {}
ProjectDir["SDG"] = "%{wks.location}/Stulu"


group "Dependencies"
include "vendor/GLFW"
include "vendor/Glad"
include "vendor/imgui"
group ""

include "SDG"
include "TestApp"

