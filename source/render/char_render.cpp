#include "char_render.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <functional>
#include <utility>


struct hash_pair final {
    template<class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const noexcept {
        uintmax_t hash = std::hash<T1>{}(p.first) << sizeof(uintmax_t)*4;
        return std::hash<uintmax_t>{}(hash ^ std::hash<T2>{}(p.second));
    }
};

static const char* red   {"\033[0;31m"};
static const char* green {"\x1B[32m"};
static const char* reset {"\x1B[0m"};

CharRender::CharRender(const CharRender::CreateConf& conf):
    outBox(conf.outBox) {
    xs.target = outBox.width;
    ys.target = outBox.height;
}

void CharRender::render(const World& world) {
    std::stringstream ss;
    const char emptySlot = ' ';
    const char actorSlot = '@';
    const int widthFactor = 1;

    setInBox(world.size);

    int height = outBox.height;
    int width = outBox.width;

    std::unordered_map<std::pair<int, int>, Actor, hash_pair> actors;

    {
        for (const auto& a : world.actors) {
            actors[{xs(a.pos.x), ys(a.pos.y)}] = a;
        }
    }

    for (int rowId = -1; rowId < height + 1; ++rowId) {
        for (int colId = -1; colId < width + 1; ++colId) {
            if (is_in(colId, 0, width) && is_in(rowId, 0, height)) {

                if (actors.count({colId, rowId}) > 0) {
                    ss << green << std::setw(widthFactor) << actorSlot << reset;
                } else {
                    ss << std::setw(widthFactor) << emptySlot;
                }

            } else if (is_in(colId, 0, width)) {
                ss << std::string(widthFactor, '-');
            } else {
                if (!is_in(rowId, 0, height)) {
                    if (colId == width && widthFactor > 1)
                        ss << "-";
                    ss << "-";
                } else {
                    if (colId == width)
                        ss << std::setw(widthFactor);
                    ss << "|";
                }
            }
        }
        ss << std::endl;
    }

    ss << std::endl;
    std::cout << ss.str();
}