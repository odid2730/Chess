project "Chess"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/"..outputdir.."/%{prj.name}")
	objdir ("%{wks.location}/bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"%{wks.location}/Engine/src",
		"%{wks.location}/Engine/vendor/glm",
		"%{wks.location}/Engine/vendor/glfw/include"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "on"
		runtime "debug"

	filter "configurations:Release"
		optimize "on"
		runtime "release"