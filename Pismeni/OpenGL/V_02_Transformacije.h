#pragma once
#include "V_01_Primitive.h"

class V_02_Transformacije :
    public V_01_Primitive
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
    V_02_Transformacije();
    virtual ~V_02_Transformacije();
    virtual void Draw();
    virtual void DrawRobot();
    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

