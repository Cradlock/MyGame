#pragma once

#include <filesystem>


class Engine{
private:
// Сервисы


public:
  Engine();
  
  void PreInit();

  void Init();

  void Run();

  void Shutdown();

private:
  
  std::filesystem::path root_path;
  

};




