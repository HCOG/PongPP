#pragma once
#include "Component.h"
#include "SDL.h"

/*This is a generic Sprite Component. It inherit the basics of the component class,
which allows it to be add/remove by an actor, and can be further derived to have 
animation and background sprite components*/
class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	//Sprite specific: draw and adding texture to actor
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	//Getters
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

	//Sprite specific component parameters
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
