#include <filesystem>
#include "filesystemutils.hxx"
#include "filesystemtypes.hxx"

namespace fs = std::filesystem;

bool FilesystemUtils::isDirPathValid(fs::path path)
{
    std::filesystem::path absolute = std::filesystem::absolute(path);
    if(std::filesystem::exists(absolute) && std::filesystem::is_directory(absolute))
    {
        return true;
    }
    return false;
}

const FilesystemTypes::DirContents FilesystemUtils::generateDirContentsFromPath(fs::path basePath)
{
    std::vector<FilesystemTypes::Entry> contents;
    for(auto& entry : std::filesystem::directory_iterator(basePath))
    {
        std::filesystem::path entryPathAbs = std::filesystem::absolute(entry.path());
        FilesystemTypes::Filetype type;
        if(entry.is_directory())
        {
            type = FilesystemTypes::Filetype::DIR;
        } else if(entry.is_regular_file())
        {
            type = FilesystemTypes::Filetype::REGULAR_FILE;
        }
        contents.push_back(FilesystemTypes::Entry(entryPathAbs, type));
    }

    return FilesystemTypes::DirContents(contents);
}
