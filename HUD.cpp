#include "HUD.h"

using namespace DungeonGame;


void HUD::InitializeHUDSprites(SDL_Renderer* pRenderer, const std::string& gemFilepath, const std::string& swordFilepath, const std::string& healthFilepath, const std::string& gameOverFilepath, const std::string& victoryFilepath, const std::string& shieldFilepath, const std::string& brokenShieldFilepath)
{
	GemTexture = LoadTexture(pRenderer, gemFilepath);
	SwordTexture = LoadTexture(pRenderer, swordFilepath);
	ShieldTexture = LoadTexture(pRenderer, shieldFilepath);
	BrokenShieldTexture = LoadTexture(pRenderer, brokenShieldFilepath);
	HealthTexture = LoadTexture(pRenderer, healthFilepath);
	GameOverTexture = LoadTexture(pRenderer, gameOverFilepath);
	VictoryTexture = LoadTexture(pRenderer, victoryFilepath);
}

void HUD::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
	int x = 0;
	//Inventory Display
	for (unsigned int i = 0; i < playerState.ItemInventory.size(); i++)
	{
		float positionX = 0;
		float positionY = 0;
		ItemType currItem = playerState.ItemInventory[i];
		switch (currItem)
		{
		case Item_GEM:
			MyTexture = GemTexture;
			break;
		case Item_SWORD:
			MyTexture = SwordTexture;
			break;
		case Item_SHIELD:
			MyTexture = ShieldTexture;
			break;
		case Item_BROKEN_SHIELD:
			MyTexture = BrokenShieldTexture;
			break;
		default:
			MyTexture = nullptr;
			break;
		}

		if (MyTexture != nullptr)
		{
			if (MyTexture == SwordTexture)
			{
				positionX = 16.0f;
				positionY = 176.0f;
			} 
			else if (MyTexture == GemTexture)
			{
				x = i;
				if (x > 1)
				{
					x = 2;
				}
				positionX = 16.0f + (48.0f * x);
				positionY = 96.0f;
			}
			else if (MyTexture == ShieldTexture || MyTexture == BrokenShieldTexture)
			{
				positionX = 64.0f;
				positionY = 176.0f;
			}

			SDL_Rect destRect = {
				(int)positionX,
				(int)positionY,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
	}

	//Health Display
	for (unsigned int i = 0; i < playerState.PlayerHP; i++)
	{
		MyTexture = HealthTexture;

		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = {
				(int)(16.0f + 48.0f * i),
				(int)16.0f,
				(int)Size.X,
				(int)Size.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}
	}

	if (playerState.PlayerHP <= 0)
	{
		SDL_Rect destRect = {
				200,
				50,
				822,
				720 };
		SDL_RenderCopy(pRenderer, GameOverTexture, nullptr, &destRect);
	}

	if (playerState.PlayerHasWon)
	{
		SDL_Rect destRect = {
				300, 
				250,
				800,
				277 };
		SDL_RenderCopy(pRenderer, VictoryTexture, nullptr, &destRect);
	}
}


