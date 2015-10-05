#include <RePlex.h>
#include <Test.h>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>

const char* g_Test_v1 =
  "#include \"pub/Test.h\"\n"
  "int bar = 3;\n"
  "int foo(int x)\n"
  "{\n"
  "  return x + 5;\n"
  "}";

const char* g_Test_v2 =
  "#include \"pub/Test.h\"\n"
  "int bar = -2;\n"
  "int foo(int x)\n"
  "{\n"
  "  return x - 5;\n"
  "}";

class RePlexTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    WriteFile("test/Test.cpp", g_Test_v1);
    Compile(1);
    TestModule::LoadLibrary();
  }

  void ChangeAndReload()
  {
    WriteFile("test/Test.cpp", g_Test_v2);
    Compile(2);
    TestModule::ReloadLibrary();
  }

  virtual void TearDown()
  {
    TestModule::UnloadLibrary();
    WriteFile("test/Test.cpp", g_Test_v1);
    Compile(1);
  }

private:
  void WriteFile(const char* path, const char* text)
  {
    // Open an output filetream, deleting existing contents
    std::ofstream out(path, std::ios_base::trunc | std::ios_base::out);
    out << text;
  }

  void Compile(int version)
  {
    if (version == m_version)
    {
      return;
    }

    m_version = version;
    EXPECT_EQ(std::system("make"), 0);
    sleep(1);
  }

  int m_version = 1;
};

TEST_F(RePlexTest, VariableReload)
{
  EXPECT_EQ(TestModule::GetBar(), 3);
  ChangeAndReload();
  EXPECT_EQ(TestModule::GetBar(), -2);
}

TEST_F(RePlexTest, FunctionReload)
{
  EXPECT_EQ(TestModule::Foo(4), 9);
  ChangeAndReload();
  EXPECT_EQ(TestModule::Foo(4), -1);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
