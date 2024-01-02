#pragma once
#include "SpriteComponent.h"
#include "Paddle.h"
#include <vector>
#include "Cust_Math.h"

//Similar Idea to the animation sprite, for more detail revisit the AnimSprite
class PaddleSpriteComponent : public SpriteComponent
{
public:
	// Set draw order to default to lower (so it's in the background)
	PaddleSpriteComponent(class Paddle* owner, int drawOrder = 100);
	
    // Update/draw overriden from parent
	void Draw(SDL_Renderer* renderer) override;

private:
    Paddle*pOwner;	
};
