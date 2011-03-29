#ifndef _EFFECT_H_
#define _EFFECT_H_

class Technique;

class Effect
{
public:
    virtual ~Effect() {}

protected:
    Effect() {}

public:
    virtual void SetTechniqueByName(const char* name) = 0;

    virtual unsigned int Begin() = 0;
    virtual void BeginPass(unsigned int passNum) = 0;

    virtual void End() = 0;
    virtual void EndPass() = 0;
};

#endif
