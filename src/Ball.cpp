#include "Ball.h"
#include "Game.h"
#include "SpriteComponent.h"

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
    SetDirection(Vector2::Normalize(Vector2(1.f, 2.f)));
    asc->SetTexture(texture);
	asc->SetTexHeight(SBB.R*2);
	asc->SetTexWidth(SBB.R*2);
    
}

bool Ball::CheckCollisionCapsuleSphere(const CapsuleBB& capsule, const SphericBB& sphere, int playernum) 
{
    Vector2 start, end, closestPoint;

    if (playernum == 0)
    {
        end = capsule.R;
        start = capsule.L;
    }
    
    else if (playernum == 1)
    {
        end = capsule.L;
        start = capsule.R;    
    }

    Vector2 segment = end - start;
    Vector2 sphereToSegmentStart = sphere.C - start;

    // Project sphere center onto the segment (consider the segment as a line)
    float t = (sphereToSegmentStart.x * segment.x + sphereToSegmentStart.y * segment.y) / (segment.x * segment.x + segment.y * segment.y);

    // Clamp the projected point to the segment
    t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;

    // Find the closest point on the segment to the sphere
    closestPoint.x = start.x + t * segment.x;
    closestPoint.y = start.y + t * segment.y;
    
    // Check if the closest point is within the sphere
    Vector2 closestPointToSphereCenter = sphere.C - closestPoint;
    float distanceSquared = closestPointToSphereCenter.Vector2::LengthSq();
    float radiusSum = capsule.radius + sphere.R;

    return distanceSquared <= (radiusSum * radiusSum);
}

void Ball::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

    //Speed update
    if (V.TS > V.S) V.TS -= 10.f;
    else V.TS = V.S;
    
    //Get the position of the ball
    Vector2 BallPos = GetPosition();
    BallPos += GetDirection() * GetSpeed() * deltaTime;
    SetPosition(BallPos);
    SetCenter(BallPos);

	////////////////////////////////////////////////////////////////
    //////////   Check for collision with the wall   ///////////////
    ////////////////////////////////////////////////////////////////

    if (SBB.C.y <= SBB.R || SBB.C.y >= (768.f-SBB.R))
    {
        //Get the direction of the ball
        Vector2 BallDir = GetDirection();

        //Reverse the direction of the ball
        BallDir.y = -BallDir.y;
        SetDirection(BallDir);
    }

    if (SBB.C.x <= SBB.R || SBB.C.x >= (1024.f-SBB.R))
    {
        //Get the direction of the ball
        Vector2 BallDir = GetDirection();

        //Reverse the direction of the ball
        BallDir.x = -BallDir.x;
        SetDirection(BallDir);
    }

    ////////////////////////////////////////////////////////////////////
    //////////   Check for collision with the paddle   ////////////////
    ////////////////////////////////////////////////////////////////////

    if (SBB.C.x <= 512.f)
    {
        if(CheckCollisionCapsuleSphere(LPaddle.GetBB(), SBB, 0))
        {
            int pstate = LPaddle.GetState();
            //Get the direction of the ball
            Vector2 BallDir = GetDirection();
            if (pstate == Paddle::PState::Moving)
            {
                //Reverse the direction of the ball
                BallDir.x = -BallDir.x;
                SetDirection(BallDir);
            }

            else if (pstate == Paddle::PState::Slamming)
            {
                BallDir.x = -BallDir.x;
                SetDirection(BallDir);
                V.TS += 750.f;
            }
            
        }
    }
    else if (SBB.C.x > 512.f)
    {
        if (CheckCollisionCapsuleSphere(RPaddle.GetBB(), SBB, 1))
        {
            int pstate = LPaddle.GetState();
            //Get the direction of the ball
            Vector2 BallDir = GetDirection();
            if (pstate == Paddle::PState::Moving)
            {
                //Reverse the direction of the ball
                BallDir.x = -BallDir.x;
                SetDirection(BallDir);
            }

            else if (pstate == Paddle::PState::Slamming)
            {
                BallDir.x = -BallDir.x;
                SetDirection(BallDir);
                V.TS += 750.f;
            }
        }
    }
}


