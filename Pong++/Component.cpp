// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Component.h"
#include "Actor.h"

//Default constructor, declaring its owner and the update order, adding itself to the owner's list of components
Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	// Add to actor's vector of components
	mOwner->AddComponent(this);
}

//Default destructor, when not overrid, simply remove itself
Component::~Component()
{
	mOwner->RemoveComponent(this);
}

//Default update do not have function, is specific component dependent
void Component::Update(float deltaTime)
{
}
