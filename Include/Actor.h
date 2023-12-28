#pragma once
#include <vector>
#include "Cust_Math.h"

//The "Actor" class is the base class for all the derived characters (ball and paddle)//
class Actor
{
public:
	/*All "Actors" will have one of the three states, depending on different state
	,it will generate different output. Declare the three states here.*/	
	enum State
	{
		EActive,			//The actor is active
		EPaused,			//The actor is on pause
		EDead				//The actor is dead
	};

	//The default constructor will take in our master game class, and set some initial values
	Actor(class Game* game);
	virtual ~Actor();		//Using virtual here to remove different actors

	////////////////////////////////////////////////////////////////
	//////////////////          Updates         ////////////////////
	////////////////////////////////////////////////////////////////

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	////////////////////////////////////////////////////////////////
	//////////////////      Getters/setters     ////////////////////
	////////////////////////////////////////////////////////////////

	//Get/set parameters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	//Get/set states
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	
	//Get game
	class Game* GetGame() { return mGame; }

	////////////////////////////////////////////////////////////////
	//////////////////    Add/Remove component  ////////////////////
	////////////////////////////////////////////////////////////////

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
