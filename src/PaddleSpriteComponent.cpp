#include "PaddleSpriteComponent.h"
#include "Actor.h"

//Inherit the constructor from the SpriteComponent
PaddleSpriteComponent::PaddleSpriteComponent(class Paddle* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
    , pOwner(owner)
{
}

/*An unique update function for the paddle sprite component, this is a modification made to handle 
the unique rotational */
void PaddleSpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * pOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * pOwner->GetScale());
		
        if(pOwner->GetPstate() == Paddle::PState::Moving || pOwner->GetPstate() == Paddle::PState::Slamming)
        {
            r.x = static_cast<int>(pOwner->GetPosition().x - r.w / 2);
            r.y = static_cast<int>(pOwner->GetPosition().y - r.h / 2);
        }

        if (pOwner->Paddle::GetPlayernum() == 0)
        {
            if (pOwner->GetPstate() == Paddle::PState::LSlapping)
            {
                Vector2 center = pOwner->GetLeftPivot();
                Vector2 point = center + Vector2(-r.w / 2.f, 0.f);
                Vector2 rotated = Vector2::RotateAroundPoint(point, center, pOwner->GetRotation());
                r.x = static_cast<int>(rotated.x);
                r.y = static_cast<int>(rotated.y);
            }
            else if (pOwner->GetPstate() == Paddle::PState::RSlapping)
            {
                Vector2 center = pOwner->GetRightPivot();
                Vector2 point = center + Vector2(-r.w / 2.f, -r.h);
                Vector2 rotated = Vector2::RotateAroundPoint(point, center, -pOwner->GetRotation());
                r.x = static_cast<int>(rotated.x);
                r.y = static_cast<int>(rotated.y);
            }
        }

        else if (pOwner->Paddle::GetPlayernum() == 1)
        {
            if (pOwner->GetPstate() == Paddle::PState::LSlapping)
            {
                Vector2 center = pOwner->GetLeftPivot();
                Vector2 point = center + Vector2(-r.w / 2, -92.5f);
                Vector2 rotated = Vector2::RotateAroundPoint(point, center, -pOwner->GetRotation());
                r.x = static_cast<int>(rotated.x);
                r.y = static_cast<int>(rotated.y);
            }
            else if (pOwner->GetPstate() == Paddle::PState::RSlapping)
            {
                Vector2 center = pOwner->GetRightPivot();
                Vector2 point = center + Vector2(-r.w / 2, -7.5f);
                Vector2 rotated = Vector2::RotateAroundPoint(point, center, pOwner->GetRotation());
                r.x = static_cast<int>(rotated.x);
                r.y = static_cast<int>(rotated.y);
            }
        }

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&r,
			-pOwner->GetRotation(),
			nullptr,
			SDL_FLIP_NONE);
	}
}