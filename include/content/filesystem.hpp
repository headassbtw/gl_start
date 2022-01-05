#pragma once
#include <string>
namespace Content{
    namespace Filesystem{
        void Initialize(bool virt);
        void Initialize(bool virt, const char* contentfolderpath);
        std::string GetText(const char* filepath);
    }
}