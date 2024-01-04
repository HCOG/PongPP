#pragma once
#include "Actor.h"

/*Define a capsule bound box structure for the paddle, the pivot should be at 7.5,7.5*/
struct CapsuleBB
{
	Vector2 L;		//Left pivot
	Vector2 R;		//Right pivot
	float radius;	//Radius
	float A;		//Angle
};

class Paddle : public Actor
{
public:
	/*Action state of player controlled paddle, modified during keyprocessing stage.
	Using to decide which action to take during updating stage*/
	enum PState
	{
		Moving,
		Slamming,
		LSlapping,
		RSlapping
	};

	Paddle(class Game* game,int playernum);
	void ProcessKeyboard(const uint8_t* state);
	void UpdateActor(float deltaTime) override;

	float GetVerticalSpeed() const { return VertiSpeed; }
	void SetVerticalSpeed(float Vertical) { VertiSpeed = Vertical;  }
	float GetRotationSpeed() const { return RotateSpeed; }
	void SetRotateSpeed(float Rotation) { VertiSpeed = RotateSpeed; }
	int GetPstate() const { return pstate; }
	int GetPlayernum() const { return mPlayernum; }
	void SetRadius(float Radius) { BB.radius = Radius; }
	CapsuleBB GetBB() const { return BB; }
	
	Vector2 GetLeftPivot() const { return BB.L; }
	Vector2 GetRightPivot() const { return BB.R; }

private:
	float VertiSpeed;				//The speed that the paddle will move vertically
	float RotateSpeed;				//The speed that the paddle will rotate (left/right)
	float SlamSpeed;				//The speed that the paddle will move horizontally (Slamming)

	float H;						//The height of the paddle (x.axis)
	float W;						//The width of the paddle (y.axis)

	int mPlayernum;					//The assigned player number
	CapsuleBB BB;					//The capsule bound box
	int pstate;						//The paddle state

	float slamdist;					//Used to determine at what stage is the paddle slamming
	float RotatedAngle;				//Used to determine at what stage is the paddle slapping
};