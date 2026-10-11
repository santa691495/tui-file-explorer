#include <filesystem>
#include <vector>
#include "filesystemtypes.hxx"

namespace fs = std::filesystem;


//-----------------------------------------------------------
//----------- FilesystemTypes::Entry ------------------------
//-----------------------------------------------------------
FilesystemTypes::Entry::Entry(std::filesystem::path path, Filetype type) :
    entry(std::pair(path, type))
{}

const fs::path FilesystemTypes::Entry::getPath() const
{
    return entry.first;
}

std::string FilesystemTypes::Entry::getPathAsStr() const
{
    return std::string(entry.first);
}

std::string FilesystemTypes::Entry::getPathFileNameAsStr() const
{
    fs::path filename = getPath().filename();
    return std::string(filename);
}

const FilesystemTypes::Filetype FilesystemTypes::Entry::getFileType() const
{
    return entry.second;
}

//-----------------------------------------------------------
//----------- FilesystemTypes::DirContents ------------------
//-----------------------------------------------------------
FilesystemTypes::DirContents::DirContents(std::vector<Entry> contents) :
    contents(contents)
{}

const std::vector<FilesystemTypes::Entry> FilesystemTypes::DirContents::getContents() const
{
    return contents;
}
