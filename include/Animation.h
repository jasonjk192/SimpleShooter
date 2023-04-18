#ifndef ANIMATION_H
#define ANIMATION_H

#include "Drawer.h"
#include "Texture.h"

#include <vector>

class Animation
{
public:
	struct AnimationParams
	{
		float animSpeed = 0;
		std::vector<Texture*> animFrames;
		SDL_FPoint animPosition{ 0,0 };
		float animRotation = 0;
		bool isLooping = false;
	};

	Animation(Drawer* aDrawer, AnimationParams animParams);
	~Animation(void);

	void Update(float aTime);
	void Draw();

	void Play() { isPlaying = true; }
	void Pause() { isPlaying = false; }
	void Stop() { isPlaying = false; currentFrame = 0; currentAnimTime = 1.f/myParams.animSpeed; }
	
	bool IsPlaying() { return isPlaying; }

	AnimationParams* GetParams() { return &myParams; }
	SDL_Point* GetFrameSize() const { return myParams.animFrames[0]->GetSize(); }

private:
	Drawer* myDrawer;

	bool isPlaying;

	AnimationParams myParams;
	float currentAnimTime;

	int currentFrame;
};

#endif // ANIMATION_H