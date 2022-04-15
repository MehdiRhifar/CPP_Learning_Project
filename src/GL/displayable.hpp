#pragma once

#include <vector>
#include <algorithm>

namespace GL {

// a displayable object can be displayed and has a z-coordinate indicating who
// is displayed before whom ;]

class Displayable
{
protected:
    float z = 0;

public:
    inline Displayable(float z_);
    inline virtual ~Displayable();

    virtual void display() const = 0;

    float get_z() const { return z; }
};

struct disp_z_cmp
{
    bool operator()(const Displayable* a, const Displayable* b) const
    {
        const auto az = a->get_z();
        const auto bz = b->get_z();
        return (az == bz) ? (a > b) : (az > bz);
    }
};

inline std::vector<const Displayable*> display_queue;

GL::Displayable::Displayable(float z_) : z { z_ } { GL::display_queue.emplace_back(this); }
GL::Displayable::~Displayable() {
    GL::display_queue.erase(std::remove(GL::display_queue.begin(), GL::display_queue.end(), this), GL::display_queue.end());
}

} // namespace GL


