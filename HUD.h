#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class HUD : public Sprite
	{
	public:
		void InitializeHUDSprites(SDL_Renderer* pRenderer, const std::string& gemFilepath, const std::string& swordFilepath, const std::string& healthFilepath, const std::string& gameOverFilepath, const std::string& victoryFilepath, const std::string& shieldFilepath, const std::string& brokenShieldFilepath);


		virtual void Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation);

	private:
		SDL_Texture* GemTexture;
		SDL_Texture* SwordTexture;
		SDL_Texture* ShieldTexture;
		SDL_Texture* BrokenShieldTexture;

		SDL_Texture* HealthTexture;

		SDL_Texture* GameOverTexture;
		SDL_Texture* VictoryTexture;

	};
}




