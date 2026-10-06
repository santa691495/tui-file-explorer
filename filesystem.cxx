#include "filesystem.hxx"
#include <filesystem>
#include <utility>
#include <vector>
#include "filetype.hxx"

std::vector<std::pair<Filetype, std::string>> Filesystem::readCurrentPathContents()
{
    std::vector<std::pair<Filetype, std::string>> dirContents;
    for(auto& entry : std::filesystem::directory_iterator(currentPath))
    {
        std::string filename = std::filesystem::absolute(entry.path());
        if(entry.is_directory())
        {
            dirContents.push_back(std::pair(Filetype::DIR, filename));
        } else {
            dirContents.push_back(std::pair(Filetype::REGULAR_FILE, filename));
        }
    }

    return dirContents;
}

//turns the path absolute and canonical
bool Filesystem::setCurrentPath(std::filesystem::path currentPath){
    if(!isDirPathValid(currentPath)){
        return false;
    } else {
        this->currentPath = std::filesystem::canonical(std::filesystem::absolute(currentPath));
        return true;
    }
}

std::filesystem::path Filesystem::getCurrentPath()
{
    return currentPath;
}

bool Filesystem::isDirPathValid(std::filesystem::path path)
{
    std::filesystem::path absolute = std::filesystem::absolute(path);
    if(std::filesystem::exists(absolute) && std::filesystem::is_directory(absolute))
    {
        return true;
    }
    return false;
}
