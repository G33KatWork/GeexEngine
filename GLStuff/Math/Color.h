#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
    Color() { c[0] = c[1] = c[2] = c[3] = 0.0f; }
    Color(const Color& oc) { c[0] = oc.R(); c[1] = oc.G(); c[2] = oc.B(); c[3] = oc.A(); }
    Color(float R, float G, float B, float A) { c[0] = R; c[1] = G; c[2] = B; c[3] = A; }

    float R() const { return c[0]; }
    float G() const { return c[1]; }
    float B() const { return c[2]; }
    float A() const { return c[3]; }

    void SetR(float R) { c[0] = R; }
    void SetG(float G) { c[1] = G; }
    void SetB(float B) { c[2] = B; }
    void SetA(float A) { c[3] = A; }

private:
    float c[4];
};

#endif
