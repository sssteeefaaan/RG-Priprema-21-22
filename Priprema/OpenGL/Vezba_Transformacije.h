#pragma once
#include "Vezba_Primitive.h"
class Vezba_Transformacije :
    public Vezba_Primitive
{
protected:
    float m_head_rot;
    float m_body_rot;
    float m_left_arm_rot;
    float m_left_underarm_rot;
    float m_right_arm_rot;
    float m_right_underarm_rot;

    float m_step;

public:
    Vezba_Transformacije();
    virtual ~Vezba_Transformacije();
    virtual void Draw();
    virtual void DrawRobot();
    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

