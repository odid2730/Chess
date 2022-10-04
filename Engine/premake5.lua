project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/"..outputdir.."/%{prj.name}")
	objdir ("%{wks.location}/bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/stb_image.h",
		"vendor/stb_image/stb_image.cpp",
		"%{IncludeDir.glm}/**.hpp",
		"%{IncludeDir.glm}/**.inl"
	}

	includedirs
	{
		"src",
		"vendor/stb_image",
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/glm"
	}

	links
	{
		"glfw",
		"glad",
		"opengl32.lib"
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	filter "files:vendor/stb_image/stb_image.cpp"
		flags "NoPCH"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "on"
		runtime "debug"

	filter "configurations:Release"
		optimize "on"
		runtime "release"