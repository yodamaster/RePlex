#pragma once
#include <array>
#include <unordered_map>
#include <string>

template <typename T, size_t NumSymbols>
class RePlexExport
{
public:
  static void Load() { GetInstance().Load(); }
  static void Reload() { GetInstance().Reload(); }

protected:
  static T& GetInstance()
  {
    static T instance;
    return instance;
  }

  RePlexLib() {}

  const char* GetPath() const = 0;

  std::array<const char*, NumSymbols>& GetSymbols() const = 0;

  template <typename Ret, typename... Args>
  Ret Execute(const char* name, Args... args)
  {
    auto symbol = std::find(name);
    if (symbol)
    {
      return reinterpret_cast<Ret(*)(Args...)>(*symbol)(args...);
    }
    else
    {
      throw std::runtime_error(std::string("Function not found: ") + name);
    }
  }

  template <typename T>
  T* GetVar(const char* name)
  {
    auto symbol = std::find(name);
    if (symbol)
    {
      return reinterpret_cast<T*>(*symbol);
    }
    else
    {
      throw std::runtime_error(std::string("Variable not found: ") + name);
    }
  }

private:
  void Load();
  void Reload();
  void LoadSymbols();

  const char* m_name;
  void* m_libHandle;
  std::unordered_map<std::string, void*> m_symbols;
}
