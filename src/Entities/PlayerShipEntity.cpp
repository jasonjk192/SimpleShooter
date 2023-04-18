#include "Entities/PlayerShipEntity.h"

PlayerShipEntity::PlayerShipEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld):
	GameCharacterEntity(aPosition, aTexture, aDrawer),
	myWorld(aWorld)
{
	myName = "PlayerShip";
	myShootCooldown = 0.1f;
	currentShootCooldown = 0.f;
	myMaxHealth = 10;
	currentHealth = 3;
	myScore = 0;

	laserSound = Mix_LoadWAV("./data/sounds/lazer.wav");
}

PlayerShipEntity::~PlayerShipEntity(void)
{
	Mix_FreeChunk(laserSound);
}

bool PlayerShipEntity::HandleEvents(SDL_Event* event)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_UP])
		myVelocity.y -= 1;
	else if (keystate[SDL_SCANCODE_DOWN])
		myVelocity.y += 1;
	if (keystate[SDL_SCANCODE_LEFT])
		myVelocity.x -= 1;
	else if (keystate[SDL_SCANCODE_RIGHT])
		myVelocity.x += 1;

	if (keystate[SDL_SCANCODE_SPACE] && currentShootCooldown<=0)
		Shoot();

	return true;
}

bool PlayerShipEntity::Update(float aTime)
{
	myDirection = SDLMaths::Normalize(myVelocity);
	myVelocity = SDLMaths::ClampMagnitude(myVelocity, myMaxSpeed);
	myPosition = { myPosition.x + aTime * myVelocity.x * myMoveSpeedMult , myPosition.y + aTime * myVelocity.y * myMoveSpeedMult };
	currentShootCooldown -= aTime;
	currentShootCooldown = std::max(currentShootCooldown, 0.f);
	return true;
}

void PlayerShipEntity::Draw()
{
	myDrawer->SetScale(myScale);
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
	myDrawer->SetScale(1.f);
}

void PlayerShipEntity::OnCollision(BaseEntity* anEntity)
{
	
}

void PlayerShipEntity::Shoot()
{
	Mix_PlayChannel(1, laserSound, 0);
	currentShootCooldown = myShootCooldown;
	auto bullet = myWorld->SpawnEntity<FriendlyBulletEntity>(myPosition, ProjectileAsset::GetInstance().GetProjectileTexture(7));
	bullet->SetOwner(this);
	bullet->SetMoveSpeedMult(1000);
	bullet->SetVelocity(myDirection);
}