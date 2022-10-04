project "glfw"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/"..outputdir.."/%{prj.name}")
	objdir ("%{wks.location}/bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",
		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

		files
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_monitor.c",
			"src/win32_time.c",
			"src/win32_thread.c",
			"src/win32_window.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

	filter "configurations:Debug"
		symbols "on"
		runtime "debug"

	filter "configurations:Release"
		optimize "on"
		runtime "release"