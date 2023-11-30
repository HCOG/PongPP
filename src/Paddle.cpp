#include "Paddle.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Paddle::Paddle(Game* game,int playernum)
	:Actor(game)
	, mPlayernum(playernum)
	, VertiSpeed(0.0f)
	, RotateSpeed(12.0f)
	, SlamSpeed(10.f)
	, pstate(Moving)
	, slamdist(0)
	, RotatedAngle(0)
	, H(100)
	, W(15)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Paddle_0.png"),
		game->GetTexture("Assets/Paddle_1.png"),
	};
	asc->SetAnimTextures(anims);
}

void Paddle::BaseLeftUpdate(Vector2 LPivot)
{

}
void Paddle::ProcessKeyboard(const uint8_t* state)
{
	/*Detection for any action state, if "pstate" is anything else 
	than moving, skip this frame of processing keyboard*/
	if (pstate != Moving) return;
	VertiSpeed = 0.0f;
	slamdist = 0.0f;
	//Input set for player one
	if (mPlayernum == 0)
	{
		//Detect moving left or with shift key, slapping left
		if (state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_LSHIFT])
		{
			VertiSpeed -= 300.0f;
		}
		else if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_LSHIFT])
		{
			pstate = LSlapping;
		}

		//Detct moving right of with shift key, slapping right
		if (state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_LSHIFT])
		{
			VertiSpeed += 300.0f;
		}
		else if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_LSHIFT])
		{
			pstate = RSlapping;
		}
		
		//Detect "W" key and shift key, and if so, SLAAAAMMMMMM
		if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_LSHIFT])
		{
			pstate = Slamming;
			Vector2 opos = GetPosition();
		}
	}

	//Input set for player two
	else if (mPlayernum == 1)
	{
		//Detect moving left or with shift key, slapping left
		if (state[SDL_SCANCODE_K] && !state[SDL_SCANCODE_RSHIFT])
		{
			VertiSpeed += 300.0f;
		}
		else if (state[SDL_SCANCODE_K] && state[SDL_SCANCODE_RSHIFT])
		{
			pstate = LSlapping;
		}

		//Detct moving right of with shift key, slapping right
		if (state[SDL_SCANCODE_SEMICOLON] && !state[SDL_SCANCODE_RSHIFT])
		{
			VertiSpeed -= 300.0f;
		}
		else if (state[SDL_SCANCODE_SEMICOLON] && state[SDL_SCANCODE_RSHIFT])
		{
			pstate = RSlapping;
		}

		//Detect "O" key and shift key, and if so, SLAAAAMMMMMM
		if (state[SDL_SCANCODE_O] && state[SDL_SCANCODE_RSHIFT])
		{
			pstate = Slamming;
		}
	}
}

void Paddle::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	/*If the action state is the default moving, simply update the paddles 
	location by moving vertically*/
	if (pstate==Moving)
	{
		Vector2 pos = GetPosition();
		pos.y += VertiSpeed * deltaTime;

		if (pos.y < (H / 2.f))
		{
			pos.y = H / 2.f;
		}
		else if (pos.y > (768.f - H / 2.f))
		{
			pos.y = 768.f - H / 2.f;
		}
		SetPosition(pos);
	}

	if (pstate == LSlapping)
	{

	}
	
	if (pstate == RSlapping)
	{

	}

	if (pstate == Slamming)
	{
		Vector2 pos = GetPosition();
		if (slamdist < 30.f)
		{
			pos.x += SlamSpeed * deltaTime;
			slamdist += SlamSpeed * deltaTime;
		}
		else if (slamdist>=30.f && slamdist<60.f)
		{
			pos.x -= SlamSpeed * deltaTime;
			slamdist += SlamSpeed * deltaTime;
		}
		else
		{
			slamdist = 0.f;
			pos.x = 100.f;
			pstate = Moving;
		}
		SetPosition(pos);
	}

}

