#pragma once
#include "StateBase.h"

class MovementFSM;

class MovementStateBase : public StateBase<MovementFSM>
{
public:
    virtual void FixedUpdate(MovementFSM* fsm) = 0; // Movement�� ���� ���� �ʿ� 
};