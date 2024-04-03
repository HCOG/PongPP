#include "Ball.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Paddle.h"
#include <iostream>
using namespace std;

Ball::Ball(Game* game, Paddle& LPaddle, Paddle& RPaddle)
	:Actor(game)
    ,LPaddle(LPaddle)
    ,RPaddle(RPaddle)
{
	// Create an paddle sprite component
    SpriteComponent* asc = new SpriteComponent(this,200);
	SDL_Texture* texture = {
		game->GetTexture("../Assets/Ball.png")
	};
    SetRadius(20.f);
    SetSpeed(400.f);
    SetDirection(Vector2::Normalize(Vector2(1.f, 0.f)));

    asc->SetTexture(texture);
	asc->SetTexHeight(SBB.R*2);
	asc->SetTexWidth(SBB.R*2);
}

/*A modified version of a collision detection code for capsule and sphere bound box. Due
to the nature of fast flying ball and paddle, I added idea from swept sphere detection model
to calculate if detection could happen between frames.*/
bool Ball::CheckCollisionCapsuleSphere(const CapsuleBB& capsule, const SphericBB& sphere, Vector2& outClosestPoint, int playernum) 
{
    Vector2 start = (playernum == 0) ? capsule.NL : capsule.NR;
    Vector2 end = (playernum == 0) ? capsule.NR : capsule.NL;

    Vector2 segment = end - start;
    Vector2 sphereToSegmentStart = sphere.NC - start;

    // Project sphere center onto the segment (consider the segment as a line)
    float t = (sphereToSegmentStart.x * segment.x + sphereToSegmentStart.y * segment.y) / (segment.x * segment.x + segment.y * segment.y);

    // Clamp the projected point to the segment
    t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;

    // Find the closest point on the segment to the sphere
    Vector2 closestPoint = start + t * segment;
    outClosestPoint = closestPoint;

    // Check if the closest point is within the sphere
    Vector2 closestPointToSphereCenter = sphere.NC - closestPoint;
    float distanceSquared = closestPointToSphereCenter.Vector2::LengthSq();
    float radiusSum = capsule.radius + sphere.R;

    return distanceSquared <= (radiusSum * radiusSum);
}


void Ball::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

    //Speed update
    if (V.TS > V.S) V.TS -= 1.f;
    else V.TS = V.S;
    
    //Get the position of the ball
    Vector2 BallPos = GetPosition();
    
    //Set the updated ball position
    BallPos += GetDirection() * GetSpeed() * deltaTime;
    SetPosition(BallPos);
    SetCenter(BallPos);
    
    //Set the predicted ball position
    BallPos += GetDirection() * GetSpeed() * deltaTime;
    SetNextCenter(BallPos);

	////////////////////////////////////////////////////////////////
    //////////   Check for collision with the wall   ///////////////
    ////////////////////////////////////////////////////////////////
    bool collide_with_wall = false;
    if (SBB.C.y <= SBB.R || SBB.C.y >= (768.f-SBB.R))
    {
        //Force apply the location to the wall
        if (SBB.C.y <= SBB.R) {
            // Force apply the location to just outside the top wall
            SBB.C.y = SBB.R;
        } else if (SBB.C.y >= (768.f - SBB.R)) {
            // Force apply the location to just outside the bottom wall
            SBB.C.y = 768.f - SBB.R;
        }

        //Get the direction of the ball
        Vector2 BallDir = GetDirection();

        //Reverse the direction of the ball
        BallDir.y = -BallDir.y;
        SetDirection(BallDir);
        collide_with_wall = true;
    }

    if (SBB.C.x <= SBB.R || SBB.C.x >= (1024.f-SBB.R))
    {
        //Force apply the location to the wall
        if (SBB.C.x <= SBB.R) {
            // Force apply the location to just outside the top wall
            SBB.C.x = SBB.R + 0.5f;
        } else if (SBB.C.x >= (1024.f - SBB.R)) {
            // Force apply the location to just outside the bottom wall
            SBB.C.x = 1023.f - SBB.R;
        }

        //Get the direction of the ball
        Vector2 BallDir = GetDirection();

        //Reverse the direction of the ball
        BallDir.x = -BallDir.x;
        SetDirection(BallDir);
        collide_with_wall = true;
    }

    if (collide_with_wall) return;
    ////////////////////////////////////////////////////////////////////
    //////////    Check for collision with the paddle   ////////////////
    ////////////////////////////////////////////////////////////////////

    if (SBB.C.x <= 512.f)
    {   
        Vector2 closestPoint;
        if(CheckCollisionCapsuleSphere(LPaddle.GetBB(), SBB, closestPoint,0))
        {
            int pstate = LPaddle.GetPstate();
            Vector2 pos = LPaddle.GetPosition();

            //Get the direction of the ball
            Vector2 BallDir = GetDirection();
            Vector2 BallPos = GetPosition();
            float tempspeed = GetSpeed();
            
            if (pstate == Paddle::PState::Moving)
            {
                //Reverse the direction of the ball
                BallPos.x = pos.x + LPaddle.GetRadius() + GetRadius();
                SetPosition(BallPos);

                BallDir.x = -BallDir.x;
                SetDirection(BallDir);
                cout<<"Moving"<<endl;
            }

            else if (pstate == Paddle::PState::Slamming)
            {
                BallPos.x = pos.x + LPaddle.GetRadius() + GetRadius();
                BallDir.x = -BallDir.x;
                tempspeed += 150.f;

                SetPosition(BallPos);
                SetDirection(BallDir);
                SetTempSpeed(tempspeed);
                cout<<"Slamming"<<endl;
            }

            else if (pstate == Paddle::PState::LSlapping || pstate == Paddle::PState::RSlapping)
            {
                float rotationAngle = -LPaddle.GetRotation();
                cout<<"Slapping"<<endl;
                cout<<rotationAngle<<endl;

                Vector2 reflectedDir = Vector2::DegreeToUnitVector(rotationAngle);
                cout<<reflectedDir.x<<" "<<reflectedDir.y<<endl;
                SetDirection(reflectedDir);

                float speed = GetSpeed();
                speed += 250.f;
                SetTempSpeed(speed);

                // Update ball direction and position
                // Calculate the direction from the paddle to the ball
                Vector2 directionFromPaddleToBall = Vector2::Normalize(SBB.NC - closestPoint);

                // Set the ball's position to be the sum of the paddle's radius, ball's radius and closest point
                BallPos.x = closestPoint.x + directionFromPaddleToBall.x * (LPaddle.GetRadius() + GetRadius());
                BallPos.y = closestPoint.y + directionFromPaddleToBall.y * (LPaddle.GetRadius() + GetRadius());

                SetPosition(BallPos);
            }
        }
    }
    else if (SBB.C.x > 512.f)
    {
        Vector2 closestPoint;
        if (CheckCollisionCapsuleSphere(RPaddle.GetBB(), SBB, closestPoint,1))
        {
            int pstate = RPaddle.GetPstate();
            Vector2 pos = RPaddle.GetPosition();

            //Get the direction of the ball
            Vector2 BallDir = GetDirection();
            Vector2 BallPos = GetPosition();
            float tempspeed = GetSpeed();

            if (pstate == Paddle::PState::Moving)
            {
                //Reverse the direction of the ball
                BallDir.x = -BallDir.x;
                SetDirection(BallDir);
            }

            else if (pstate == Paddle::PState::Slamming)
            {
                BallPos.x = pos.x - RPaddle.GetRadius() - GetRadius();
                BallDir.x = -BallDir.x;
                tempspeed += 150.f;

                SetPosition(BallPos);
                SetDirection(BallDir);
                SetTempSpeed(tempspeed);
            }
        }
    }
}


