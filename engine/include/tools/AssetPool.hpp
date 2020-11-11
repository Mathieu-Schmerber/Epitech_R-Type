//
// Created by mathi on 09/11/2020.
//

#ifndef RTYPE_ASSETPOOL_HPP
#define RTYPE_ASSETPOOL_HPP

#include <string>
#include <vector>

namespace Engine {

    class AssetPool {
    private:
        std::vector<std::string> _assets;

        void getAssetsRecursively(const std::string &root);
    public:
        explicit AssetPool(const std::string &root);

        [[nodiscard]] size_t getIndexFromPath(const std::string &path) const;
        [[nodiscard]] std::string getPathFromIndex(size_t index) const;

        void addAsset(const std::string &path);
    };
}


#endif //RTYPE_ASSETPOOL_HPP
