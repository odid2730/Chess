project "glad"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/"..outputdir.."/%{prj.name}")
	objdir ("%{wks.location}/bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "on"
		runtime "debug"

	filter "configurations:Release"
		optimize "on"
		runtime "release"