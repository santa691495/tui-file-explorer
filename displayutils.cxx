#include "displayutils.hxx"
#include "filesystemtypes.hxx"
#include <filesystem>
#include <map>

const std::map<int, std::filesystem::path> DisplayUtils::generateLineNumToPathMapping(
    int lineNumStart, FilesystemTypes::DirContents dirContents
)
{
    int optionIndex = 0;
    std::map<int, std::filesystem::path> mapping;
    for(FilesystemTypes::Entry entry: dirContents.getContents())
    {
        mapping.insert({lineNumStart + optionIndex, entry.getPath()});
        ++optionIndex;
    }

    return mapping;
}
