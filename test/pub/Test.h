#pragma once

#include <RePlex.h>

extern "C"
{
  int foo(int);
  extern int bar;
}

std::array<std::pair<const char*, void*>, 2> g_exports = {
  std::make_pair("foo", nullptr),
  std::make_pair("bar", nullptr)
};

class TestModule : public RePlexModule<TestModule, g_exports.size()>
{
public:
  static int Foo(int input)
  {
    return GetInstance().Execute<0, int, int>(input);
  }

  static int GetBar()
  {
    return *GetInstance().GetVar<1, decltype(bar)>();
  }

  TestModule() : RePlexModule(g_exports) {}

  virtual const char* GetPath() const override
  {
    return "bin/Debug/libRePlexTest.dylib";
  }
};
