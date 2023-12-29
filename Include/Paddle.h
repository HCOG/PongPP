#pragma once
#include "Actor.h"

//Define a capsule bound box structure for the paddle
struct CapsuleBB
{
	Vector2 L;		//Left pivot
	Vector2 R;		//Right pivot
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

	void BaseLeftUpdate(Vector2 LPivot);
	void BaseRightUpdate(Vector2 RPivot);
	void BaseCenterUpdate(Vector2 Center);

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