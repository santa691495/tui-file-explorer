#include <filesystem>
#include "filesystemtypes.hxx"

#ifndef FILESYSTEM_HXX
#define FILESYSTEM_HXX

//All paths must be stored as absolute and only made relative for display
class Filesystem
{
    private:
        //MUST ALWAYS BE ABSOLUTE
        std::filesystem::path currentPath = "";

    public:
        //*make separate object for this vector (like DirectoryContents)
        const FilesystemTypes::DirContents readCurrentPathContents() const;
        const std::filesystem::path getCurrentPath() const;
        bool setCurrentPath(std::filesystem::path currentPath);
        void setCurrentPathToParent();
};

#endif
