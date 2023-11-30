#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

/*Default constructor, takes in the Actor owner and draworder and calling and pass to basic 
component constructor to register the sprite to owner actor*/
SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);	//Beside register the actor owner, also register to game
}

//Default sprite destructor
SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

/*Draw function will be the final function to render the actor. It will first create
a SDL_rectangle:1.Formatting the size of the rectangle based on the member variable 
TexWidth and TexHeight and the Owner's scale; 2.Positioning the rectangle around the 
owner as the default starting point of actor is in the top left corner. It will then 
utilize the SDL_RenderCopyEx function to combined the rectangle drew and the texture
(texture obtained in next member function) and form the final render.*/
void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE);
	}
}


/*This member function will intake a SDL_Texture and formmating it to accomadate the
Draw member function above.*/
void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
