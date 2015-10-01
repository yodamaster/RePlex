workspace "RePlex"
  configurations {"Debug", "Release"}
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"
  flags { "C++14" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    flags { "Symbols" }

  filter "configurations:Release"
    defines { "RELEASE" }
    optimize "On"

  project "RePlex"
    kind "StaticLib"
    files { "lib/**.h", "lib/**.cpp", "lib/pub/*.h" }

  project "RePlexRuntime"
    kind "ConsoleApp"
    links { "RePlex" }
    files { "runtime/**.h", "runtime/**.cpp" }
    includedirs { "lib/pub", "test/pub" }

  project "RePlexTest"
    kind "SharedLib"
    files { "test/**.h", "test/**.cpp", "test/pub/*.h" }
    includedirs { "lib/pub" }