//
// Created by mathi on 09/11/2020.
//

#include <algorithm>
#include <iostream>
#include <filesystem>
#include "tools/AssetPool.hpp"

Engine::AssetPool::AssetPool(const std::string &root)
{
    this->getAssetsRecursively(root);
}

void Engine::AssetPool::addAsset(const std::string &path)
{
    this->_assets.push_back(path);
}

size_t Engine::AssetPool::getIndexFromPath(const std::string &path) const
{
    auto it = std::find(this->_assets.begin(), this->_assets.end(), path);

    if (it != this->_assets.end())
        return std::distance(this->_assets.begin(), it);
    return 0;
}

std::string Engine::AssetPool::getPathFromIndex(size_t index) const
{
    if (index < this->_assets.size())
        return this->_assets.at(index);
    return "null";
}

void Engine::AssetPool::getAssetsRecursively(const std::string &root) {
    for (std::filesystem::recursive_directory_iterator i(root), end; i != end; ++i) {
        if (!is_directory(i->path())) {
            this->_assets.push_back(i->path().relative_path().string());
            std::replace(this->_assets.back().begin(), this->_assets.back().end(), '\\', '/');
        }
    }
}