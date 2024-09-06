#pragma once
#include "Actor.h"
#include "Paddle.h"

/*Define a capsule bound box structure for the paddle*/
struct SphericBB
{
	Vector2 C;		//Center
    Vector2 NC;     //Next center
    float R;		//Radius
};

struct Velocity
{
    Vector2 D;		//Direction: unit vector to determine the direction of the ball
    float S;		//Speed: baseline scalar speed to record the constant speed of the ball
    float TS;       //Temporary speed: used to store the increased speed of the ball after it hits the paddle
};

class Ball : public Actor
{
public:

	Ball(class Game* game, Paddle& LPaddle, Paddle& RPaddle);
	void UpdateActor(float deltaTime) override;
    static bool CheckCollisionCapsuleSphere(const CapsuleBB& capsule, const SphericBB& sphere, Vector2& outClosestPoint, int playernum);

    //Getters and setters
    float GetSpeed() const { return V.TS; }
    float GetRadius() const { return SBB.R; }
	Vector2 GetDirection() const { return V.D; }
    Vector2 GetCenter() const { return SBB.C; }
    Vector2 GetNextCenter() const { return SBB.NC; }
    
    void SetDirection(Vector2 Direction) { V.D = Direction; }
    void SetSpeed(float Speed) { V.S = Speed; }
    void SetTempSpeed(float TempSpeed) { V.TS = TempSpeed; }
    void SetCenter(Vector2 Center) { SBB.C = Center; }
    void SetNextCenter(Vector2 NextCenter) { SBB.NC = NextCenter; }
    void SetRadius(float Radius) { SBB.R = Radius; }

    void PickUpLPaddle(Paddle& Paddle) { LPaddle = Paddle; }
    void PickUpRPaddle(Paddle& Paddle) { RPaddle = Paddle; }
private:
    Velocity V;                     //The velocity of the ball
	SphericBB SBB;		            //The capsule bound box for ball
    Paddle& LPaddle;                //The left paddle
    Paddle& RPaddle;                //The right paddle
};