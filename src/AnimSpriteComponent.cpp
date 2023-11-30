#include "AnimSpriteComponent.h"
#include "Math.h"

/*The constructor will intake the Actor owner's name and draworder, and calls and pass it to 
the spriteComponent constructor, which will initiate basic Sprite properties, as well pass the 
owner and draworder to the basic component constructor and register this animation sprite component
to its owner.*/
AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)			//Pass the owner and draw order to sprite Component constructor
	, mCurrFrame(0.0f)							//Initiate the frame, set it to frame 0
	, mAnimFPS(24.0f)							//Set the frame rate to be 24fps (default)
{
}


void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}

		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
