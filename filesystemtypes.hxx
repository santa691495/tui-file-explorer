#include <filesystem>
#include <vector>
#include <string>

#ifndef FILESYSTEM_TYPES_HXX
#define FILESYSTEM_TYPES_HXX

namespace FilesystemTypes
{
    enum class Filetype
    {
        REGULAR_FILE,
        DIR,
        SYMLINK
    };

    class Entry
    {
        private:
            const std::pair<std::filesystem::path, Filetype> entry;
        public:
            explicit Entry(std::filesystem::path path, Filetype type);
            const std::filesystem::path getPath() const;
            std::string getPathAsStr() const;
            std::string getPathFileNameAsStr() const;
            const Filetype getFileType() const;
    };

    class DirContents
    {
        private:
            const std::vector<Entry> contents;
        public:
            explicit DirContents(std::vector<Entry> contents);
            const std::vector<Entry> getContents() const;
    };

}

#endif
