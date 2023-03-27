#include "Entities/BulletEntity.h"

BulletEntity::BulletEntity(const SDL_FPoint& aPosition, Texture* aTexture, Drawer* aDrawer, World* aWorld) :
	DynamicEntity(aPosition, aTexture, aDrawer),
	myWorld(aWorld),
	myLifetime(1),
	myOwner(nullptr)
{
	myName = "Bullet";
}

BulletEntity::~BulletEntity(void)
{
}

bool BulletEntity::Update(float aTime)
{
	myDirection = myVelocity;
	myPosition = { myPosition.x + aTime * myVelocity.x * myMoveSpeedMult , myPosition.y + aTime * myVelocity.y * myMoveSpeedMult };

	myLifetime -= aTime;
	if (myLifetime <= 0)
		markForDelete = true;

	return true;
}

void BulletEntity::Draw()
{
	myDrawer->Draw(myTexture, myPosition.x - myTexture->GetSize()->x / 2, myPosition.y - myTexture->GetSize()->y / 2, 90 + SDLMaths::rad2deg(SDLMaths::Angle(myDirection)));
}

void BulletEntity::OnCollision(BaseEntity* anEntity)
{
	if (anEntity == myOwner) return;
	else
	{
		anEntity->SetMarkForDelete();
		SetMarkForDelete();
	}
}

void FriendlyBulletEntity::OnCollision(BaseEntity* anEntity)
{
	if (anEntity == myOwner || dynamic_cast<PlayerShipEntity*>(anEntity)) return;
	else
	{
		if (GameCharacterEntity* myShip = dynamic_cast<GameCharacterEntity*>(anEntity))
		{
			myShip->ChangeHealth(-1);
			SetMarkForDelete();
			auto playerShip = dynamic_cast<PlayerShipEntity*>(myWorld->GetPlayerShipEntity());
			playerShip->AddScore(10);
		}
	}
}

void EnemyBulletEntity::OnCollision(BaseEntity* anEntity)
{
	if (anEntity == myOwner || dynamic_cast<EnemyShipEntity*>(anEntity)) return;
	else
	{
		if(GameCharacterEntity* myShip = dynamic_cast<GameCharacterEntity*>(anEntity))
		{
			myShip->ChangeHealth(-1);
			SetMarkForDelete();
		}
	}
}