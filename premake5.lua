include "Dependencies.lua"

workspace "Chess"
	configurations
	{
		"Debug",
		"Release"
	}
	architecture "x86_64"

group "Dependencies"
	include "Engine/vendor/glfw"
	include "Engine/vendor/glad"
group ""

include "Engine"
include "Chess"