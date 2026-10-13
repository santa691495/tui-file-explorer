#include "filesystem.hxx"
#include "filesystemtypes.hxx"
#include "filesystemutils.hxx"
#include <filesystem>

const FilesystemTypes::DirContents Filesystem::readCurrentPathContents() const
{
    return FilesystemUtils::generateDirContentsFromPath(currentPath);
}

//turns the path absolute and canonical
bool Filesystem::setCurrentPath(std::filesystem::path currentPath){
    if(!FilesystemUtils::isDirPathValid(currentPath)){
        return false;
    } else {
        this->currentPath = std::filesystem::canonical(std::filesystem::absolute(currentPath));
        return true;
    }
}

const std::filesystem::path Filesystem::getCurrentPath() const
{
    return currentPath;
}

void Filesystem::setCurrentPathToParent()
{
    setCurrentPath(currentPath.parent_path());
}
