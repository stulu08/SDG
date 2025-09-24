project "SDG"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "")
	objdir ("bin-int/" .. outputdir .. "")
	
	
	pchheader "st_pch.h"
	pchsource "src/st_pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}
	defines
	{
		--"SDG_DYNAMIC_LINK",
		--"SDG_DLL_BUILD"
	}

	includedirs
	{
		"src",
		"src/Stulu/",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
		
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"%{Library.OpenGL}"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"GLFW_INCLUDE_NONE"
		}
		

	filter "configurations:Debug"
		defines "SDG_DEBUG"
		runtime "Debug"
		optimize "off"
		symbols "on"

	filter "configurations:Release"
		defines "SDG_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines "SDG_DIST"
		runtime "Release"
		optimize "on"
		symbols "off"
