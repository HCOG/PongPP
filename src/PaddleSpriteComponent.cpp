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
		SDL_Point pivot;
        SDL_Rect r;
        Vector2 center;

		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * pOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * pOwner->GetScale());
		
        r.x = static_cast<int>(pOwner->GetPosition().x - r.w / 2);
        r.y = static_cast<int>(pOwner->GetPosition().y - r.h / 2);
        
        if(pOwner->GetPstate() == Paddle::PState::Moving || pOwner->GetPstate() == Paddle::PState::Slamming)
        { 
            pivot.x = r.w / 2;
            pivot.y = r.h / 2;
        }

        else if (pOwner->Paddle::GetPlayernum() == 0)
        {
            if (pOwner->GetPstate() == Paddle::PState::LSlapping)
            {
                center = pOwner->GetLeftPivot();
            }
            
            else if (pOwner->GetPstate() == Paddle::PState::RSlapping)
            {
                center = pOwner->GetRightPivot(); 
            }

            pivot.x = center.x - r.x;
            pivot.y = center.y - r.y;
        }

        else if (pOwner->Paddle::GetPlayernum() == 1)
        {
            if (pOwner->GetPstate() == Paddle::PState::LSlapping)
            {
                center = pOwner->GetLeftPivot();
            }
            else if (pOwner->GetPstate() == Paddle::PState::RSlapping)
            {
                center = pOwner->GetRightPivot();
            }
            
            pivot.x = center.x - r.x;
            pivot.y = center.y - r.y;
        }

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&r,
			-pOwner->GetRotation(),
			&pivot,
			SDL_FLIP_NONE);
	}
}