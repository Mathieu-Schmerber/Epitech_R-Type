//
// Created by mathi on 29/10/2020.
//

#ifndef RTYPE_AWINDOW_HPP
#define RTYPE_AWINDOW_HPP

#include <string>

namespace Engine {

    class AWindow {

    protected:
        std::pair<int, int> _size;
        std::string _title;

    public:
        AWindow(const std::string &title, const std::pair<int, int> &windowSize);
        ~AWindow() = default;

        virtual void open();
        virtual void display();
        virtual void close();

        void setSize(const std::pair<int, int> &size);
        void setTitle(const std::string &title);
        std::pair<int, int> getSize() const;
        std::string getTitle() const;

    };
}


#endif //RTYPE_AWINDOW_HPP
