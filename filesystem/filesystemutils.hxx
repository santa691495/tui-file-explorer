#include <filesystem>
#include "filesystemtypes.hxx"

#ifndef FILESYSTEM_UTILS_HXX
#define FILESYSTEM_UTILS_HXX

namespace FilesystemUtils
{
    bool isDirPathValid(std::filesystem::path path);
    const FilesystemTypes::DirContents generateDirContentsFromPath(std::filesystem::path basePath);
};

#endif
