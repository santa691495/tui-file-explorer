#include <filesystem>
#include "filesystemtypes.hxx"

#ifndef FILESYSTEM_HXX
#define FILESYSTEM_HXX

class Filesystem
{
    private:
        //MUST ALWAYS BE ABSOLUTE
        std::filesystem::path currentPath = "";

    public:
        const FilesystemTypes::DirContents readCurrentPathContents() const;
        const std::filesystem::path getCurrentPath() const;
        bool setCurrentPath(std::filesystem::path currentPath);
        void setCurrentPathToParent();
};

#endif
