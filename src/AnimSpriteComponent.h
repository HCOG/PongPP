#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	//The constructor
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

	// Update animation every frame (overriden from component)
	void Update(float deltaTime) override;

	// Set the textures used for animation
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

	//Unique properties of animation sprite
private:
	// As this is an animation, store all the textures used in the animation as a vector list
	std::vector<SDL_Texture*> mAnimTextures;
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};
