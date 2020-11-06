//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_AWINDOW_HPP
#define RTYPE_AWINDOW_HPP

#include <string>
#include <vector>
#include "tools/Geometry.hpp"

namespace Engine {

    class AWindow {

    protected:
        Size<int> _size;
        std::string _title;
        bool _vSyncEnabled = true;
        int _frameRate = 30;

    public:
        AWindow(const std::string &title, const Size<int> &windowSize);
        ~AWindow() = default;

        virtual void open() = 0;
        virtual bool isOpen() = 0;
        virtual void display() = 0;
        virtual void close() = 0;

        virtual void setFrameRate(int frameRate) = 0;
        virtual void setVsync(bool value) = 0;
        void setSize(const Size<int> &size);
        virtual void setTitle(const std::string &title);
        [[nodiscard]] Size<int> getSize() const;
        [[nodiscard]] virtual int getFrameRate() const;
        [[nodiscard]] virtual bool getVsync() const;
        [[nodiscard]] std::string getTitle() const;

    };
}


#endif //RTYPE_AWINDOW_HPP
