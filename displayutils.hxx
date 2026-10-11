#include <filesystem>
#include "filesystemtypes.hxx"
#include <map>

#ifndef DISPLAY_UTILS
#define DISPLAY_UTILS

namespace DisplayUtils {
    const std::map<int, std::filesystem::path> generateLineNumToPathMapping(
        int lineNumStart, FilesystemTypes::DirContents contents
    );
};

#endif
