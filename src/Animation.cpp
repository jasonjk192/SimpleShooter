#include "Animation.h"

#include <iostream>

Animation::Animation(Drawer* aDrawer, AnimationParams animParams):
	myDrawer(aDrawer),
	myParams(animParams),
	currentFrame(0),
	currentAnimTime(1.f / myParams.animSpeed),
	isPlaying(false)
{
}

Animation::~Animation(void)
{
}

void Animation::Update(float aTime)
{
	if(isPlaying)
	{
		currentAnimTime -= aTime;
		if (currentAnimTime <= 0.f)
		{
			currentAnimTime = 1.f / myParams.animSpeed;
			currentFrame++;
			if (currentFrame == myParams.animFrames.size())
			{
				if (myParams.isLooping)
					currentFrame = currentFrame % myParams.animFrames.size();
				else
					isPlaying = false;
			}
		}
	}
}

void Animation::Draw()
{
	myDrawer->Draw(myParams.animFrames[currentFrame],myParams.animPosition.x - myParams.animFrames[currentFrame]->GetSize()->x, myParams.animPosition.y - myParams.animFrames[currentFrame]->GetSize()->y * myDrawer->GetScale(), myParams.animRotation * myDrawer->GetScale());
}