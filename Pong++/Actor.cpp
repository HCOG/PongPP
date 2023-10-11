#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
////////////////          Default constructor           ///////////////////
///////////////////////////////////////////////////////////////////////////
Actor::Actor(Game* game)
	:mState(EActive)					//Set initial state as active
	, mPosition(Vector2::Zero)			//Set initial position
	, mScale(1.0f)						//Set initial scale
	, mRotation(0.0f)					//Set initial rotation speed
	, mGame(game)						//Set the game member to the main game class we are using
{
	mGame->AddActor(this);				//Adding the actor itself to the game (class)
}

///////////////////////////////////////////////////////////////////////////
////////////////           Default destructor           ///////////////////
///////////////////////////////////////////////////////////////////////////
Actor::~Actor()
{
	mGame->RemoveActor(this);			//Removing the actor itself from the game 
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

//Check if the actor is still alive, and if yes, then update its components and the actor itself
void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

//Update all the components
void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

//The default updateactor do not have any function, will need virtual actor specific based function
void Actor::UpdateActor(float deltaTime)
{
}

//Adding components to the end of components list
void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

//Remove components
void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}