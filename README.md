# RePlex
C++ module reloading library and runtime

This project is split into three modules (one of which is currently just a header).

1. RePlex - Header only file used for exporting modules to be reloaded and interfacing with them (provides the RePlexExport base class).
2. Test library - Library file containing some a function and variable to be exported, and a specialization of the RePlexExport class.
3. RePlexRuntime - Test executable which loads the test library, reloads it, and verifies that reloading occurred properly.
 
## Build instructions

After fetching the repository, run `git submodule init` followed by `git submodule update` to fetch the Google test framework which is required to run the tests.

You must have [premake5](https://github.com/premake/premake-core) installed and in your path. This library does not yet support Windows, but should function on OSX and Linux (Linux still untested at this time). To compile the program, invoke `premake5 [action]` in the root directory of the project, where "action" is a target IDE or supported build backend of your choice. For example:

```
premake5 xcode4
```

will generate an `.xworkspace` file you can open to compile and run the program in Xcode.
