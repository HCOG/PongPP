#include "Paddle.h"
#include "PaddleSpriteComponent.h"
#include "Game.h"

Paddle::Paddle(Game* game,int playernum)
	:Actor(game)
	, mPlayernum(playernum)
	, VertiSpeed(0.0f)
	, RotateSpeed(500.0f)
	, SlamSpeed(750.f)
	, pstate(Moving)
	, slamdist(0)
	, RotatedAngle(0)
	, H(100)
	, W(14)
{
	// Create an paddle sprite component
	PaddleSpriteComponent* asc = new PaddleSpriteComponent(this);
	SDL_Texture* texture = {
		game->GetTexture("../Assets/Paddle.png")
	};
	asc->SetTexture(texture);
	asc->SetTexHeight(H);
	asc->SetTexWidth(W);
	SetRadius(8.f);
}

void Paddle::ProcessKeyboard(const uint8_t* state)
{
	/*Detection for any action state, if "pstate" is anything else 
	than moving, skip this frame of processing keyboard*/
	if (pstate != Moving) return;
	
	//Reset the vertical speed
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
		//Set up a boundary for both paddels
		Vector2 pos = GetPosition();
		Vector2 NextPos = pos;
		pos.y += VertiSpeed * deltaTime;
		NextPos.y += 2.f * VertiSpeed * deltaTime;
		if (pos.y < (H / 2.f))
		{
			pos.y = H / 2.f;
		}
		else if (pos.y > (768.f - H / 2.f))
		{
			pos.y = 768.f - H / 2.f;
		}
		SetPosition(pos);

		if (mPlayernum == 0)
		{
			BB.NL = Vector2(NextPos.x, NextPos.y - 43.f);
			BB.NR = Vector2(NextPos.x, NextPos.y + 43.f);
		}
		else if (mPlayernum == 1)
		{
			BB.NL = Vector2(NextPos.x, NextPos.y + 43.f);
			BB.NR = Vector2(NextPos.x, NextPos.y - 43.f);
		}
	}
	
	if (mPlayernum ==0)
	{
		if (pstate == Slamming)
		{
			Vector2 pos = GetPosition();
			Vector2 nextpos = pos;
			
			if (slamdist < 100.f)
			{
				pos.x += SlamSpeed * deltaTime;
				nextpos.x += 2.f * SlamSpeed * deltaTime;
				slamdist += SlamSpeed * deltaTime;
			}
			else if (slamdist>=100.f && slamdist<200.f)
			{
				pos.x -= SlamSpeed * deltaTime;
				nextpos.x -= 2.f * SlamSpeed * deltaTime;
				slamdist += SlamSpeed * deltaTime;
			}
			else
			{
				slamdist = 0.f;
				pos.x = 100.f;
				pstate = Moving;
			}
			
			SetPosition(pos);
			BB.L = Vector2(pos.x, pos.y - 43.f);
			BB.R = Vector2(pos.x, pos.y + 43.f);
			BB.NL = Vector2(nextpos.x, nextpos.y - 43.f);
			BB.NR = Vector2(nextpos.x, nextpos.y + 43.f);
		}

		else if (pstate == LSlapping || pstate == RSlapping)
		{
			float NextA = GetRotation();
			if (RotatedAngle < 60.f)
			{
				RotatedAngle += RotateSpeed * deltaTime;
				BB.A += RotateSpeed * deltaTime;
				NextA += 2.f * RotateSpeed * deltaTime;
				SetRotation(BB.A);
			}

			else if (RotatedAngle >= 60.f && RotatedAngle < 120.f)
			{
				RotatedAngle += RotateSpeed * deltaTime;
				BB.A -= RotateSpeed * deltaTime;
				NextA -= 2.f * RotateSpeed * deltaTime;
				SetRotation(BB.A);
			}
		
			else
			{
				RotatedAngle = 0.f;
				BB.A = 0.f;
				SetRotation(0.f);
				pstate = Moving;
				
				//A mamual reset to the BoundBox's left and right pivot to prevent add up of tiny errors
				Vector2 pos = GetPosition();
				BB.L = Vector2(pos.x, pos.y - 43.f);
				BB.R = Vector2(pos.x, pos.y + 43.f);
				return;
			}
			
			if (pstate == LSlapping)
			{
				BB.R = Vector2::FindNewPoint(BB.L, Math::ToRadians(90.f-BB.A), 86.f);
				BB.NR = Vector2::FindNewPoint(BB.L, Math::ToRadians(90.f-NextA), 86.f);
			}

			else if (pstate == RSlapping)
			{
				SetRotation(-BB.A);
				BB.L = Vector2::FindNewPoint(BB.R, Math::ToRadians(-90.f+BB.A), 86.f);
				BB.NL = Vector2::FindNewPoint(BB.R, Math::ToRadians(-90.f+NextA), 86.f);
			}
		}
	}
	
	if (mPlayernum ==1)
	{
		if (pstate == Slamming)
		{
			Vector2 pos = GetPosition();
			Vector2 nextpos = pos;
			if (slamdist < 100.f)
			{
				pos.x -= SlamSpeed * deltaTime;
				nextpos.x -= 2 * SlamSpeed * deltaTime;
				slamdist += SlamSpeed * deltaTime;
			}
			else if (slamdist>=100.f && slamdist<200.f)
			{
				pos.x += SlamSpeed * deltaTime;
				nextpos.x += SlamSpeed * deltaTime;
				slamdist += SlamSpeed * deltaTime;
			}
			else
			{
				slamdist = 0.f;
				pos.x = 900.f;
				pstate = Moving;
			}
			SetPosition(pos);
			BB.L = Vector2(pos.x, pos.y + 43.f);
			BB.R = Vector2(pos.x, pos.y - 43.f);
			BB.NL = Vector2(nextpos.x, nextpos.y + 43.f);
			BB.NR = Vector2(nextpos.x, nextpos.y - 43.f);
		}

		else if (pstate == LSlapping || pstate == RSlapping)
		{
			if (RotatedAngle < 60.f)
			{
				RotatedAngle += RotateSpeed * deltaTime;
				BB.A += RotateSpeed * deltaTime;
				SetRotation(BB.A);
			}

			else if (RotatedAngle >= 60.f && RotatedAngle < 120.f)
			{
				RotatedAngle += RotateSpeed * deltaTime;
				BB.A -= RotateSpeed * deltaTime;
				SetRotation(BB.A);
			}
		
			else
			{
				RotatedAngle = 0.f;
				BB.A = 0.f;
				SetRotation(0.f);
				pstate = Moving;

				//A mamual reset to the BoundBox's left and right pivot to prevent add up of tiny errors
				Vector2 pos = GetPosition();
				BB.L = Vector2(pos.x, pos.y + 43.f);
				BB.R = Vector2(pos.x, pos.y - 43.f);
				return;
			}
			
			if (pstate == LSlapping)
			{
				BB.R = Vector2::FindNewPoint(BB.L, Math::ToRadians(BB.A-90.f), 86.f);
			}

			else if (pstate == RSlapping)
			{
				SetRotation(-BB.A);
				BB.L = Vector2::FindNewPoint(BB.R, Math::ToRadians(90.f-BB.A), 86.f);
			}
		}
	}
}

