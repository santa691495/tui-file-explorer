#include <filesystem>
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

        std::vector<std::pair<Filetype, std::filesystem::path>> readCurrentPathContents();
        bool setCurrentPath(std::filesystem::path currentPath);
        std::filesystem::path getCurrentPath();
        void setCurrentPathToParent();

    private:
        bool isDirPathValid(std::filesystem::path path);
};

#endif
