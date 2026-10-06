#include <filesystem>
#include <string>
#include <utility>
#include <vector>
#include "filetype.hxx"

#ifndef FILESYSTEM_HXX
#define FILESYSTEM_HXX

class Filesystem
{
    private:
        //MUST ALWAYS BE ABSOLUTE
        std::filesystem::path currentPath = "";

    public:

        std::vector<std::pair<Filetype, std::string>> readCurrentPathContents();
        bool setCurrentPath(std::filesystem::path currentPath);
        std::filesystem::path getCurrentPath();

    private:
        bool isDirPathValid(std::filesystem::path path);
};

#endif
