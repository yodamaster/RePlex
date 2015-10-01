#pragma once

#include <array>
#include <unordered_map>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <cassert>

template <typename E, size_t NumSymbols>
class RePlexModule
{
public:
  using SymbolArray = std::array<std::pair<const char*, void*>, NumSymbols>;

  static void LoadLibrary() { GetInstance().Load(); }
  static void ReloadLibrary() { GetInstance().Reload(); }

protected:
  static E& GetInstance()
  {
    static E instance;
    return instance;
  }

  RePlexModule(SymbolArray& symbols) : m_symbols(symbols) {}

  virtual const char* GetPath() const = 0;

  template <size_t Index, typename Ret, typename... Args>
  Ret Execute(Args... args)
  {
    static_assert(Index >= 0 && Index < NumSymbols, "Out of bounds symbol index");

    auto symbol = m_symbols[Index];
    return reinterpret_cast<Ret(*)(Args...)>(symbol.second)(args...);
  }

  template <size_t Index, typename T>
  T* GetVar()
  {
    static_assert(Index >= 0 && Index < NumSymbols, "Out of bounds symbol index");

    auto symbol = m_symbols[Index];
    return static_cast<T*>(symbol.second);
  }

private:
  void Load()
  {
    m_libHandle = dlopen(GetPath(), RTLD_NOW);
    assert(m_libHandle);
    LoadSymbols();
  }

  void Reload()
  {
    dlclose(m_libHandle);
    Load();
  }

  void LoadSymbols()
  {
    for (auto&& symbol : m_symbols)
    {
      symbol.second = dlsym(m_libHandle, symbol.first);
    }
  }

  void* m_libHandle;
  SymbolArray& m_symbols;
};
