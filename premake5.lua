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

  project "GoogleTest"
    kind "StaticLib"
    files { "googletest/googletest/src/gtest-all.cc" }
    includedirs { "googletest/googletest/include", "googletest/googletest" }

  project "RePlexRuntime"
    kind "ConsoleApp"
    files { "runtime/**.h", "runtime/**.cpp" }
    includedirs { "lib/pub", "test/pub", "googletest/googletest/include" }
    links { "GoogleTest" }

  project "RePlexTest"
    kind "SharedLib"
    files { "test/**.h", "test/**.cpp", "test/pub/*.h" }
    includedirs { "lib/pub" }

