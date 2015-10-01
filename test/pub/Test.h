#pragma once

#include <RePlex.h>

extern "C"
{
  void foo(int);
  extern int bar;
}

std::array<std::pair<const char*, void*>, 2> g_exports = {
  std::make_pair("foo", nullptr),
  std::make_pair("bar", nullptr)
};

class TestModule : public RePlexModule<TestModule, g_exports.size()>
{
public:
  static void Foo(int input)
  {
    GetInstance().Execute<0, void, int>(input);
  }

  static int GetBar()
  {
    return *GetInstance().GetVar<1, decltype(bar)>();
  }

  TestModule() : RePlexModule(g_exports) {}

protected:
  virtual const char* GetPath() const override
  {
#ifdef DEBUG
    return "bin/Debug/libRePlexTest.dylib";
#else
    return "bin/Release/libRePlexTest.dylib";
#endif
  }
};
