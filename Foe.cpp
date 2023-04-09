#include "Foe.h"

using namespace DungeonGame;

void Foe::SetFoeIndex(int newIndex)
{
	FoeIndex = newIndex;
}


void Foe::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	const float FOE_MOVEMENT_SPEED = 100.0f;
	int counter = 0;
	FoeData& currFoe = worldState.Foes[FoeIndex];

	if (currFoe.Alive && !playerState.PlayerHasWon)
	{
		Vector2d vecToPlayer = currFoe.Position - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			if (playerState.PlayerHP > 0 && playerState.InvincibilitySeconds <= 0.0f)
			{
				if (playerState.canDefeatFoe)
				{
					currFoe.Alive = false;
					worldState.FoeDefeated = true;
				}
				else if (playerState.invulnerable)
				{
					counter++;
					playerState.InvincibilitySeconds = 1.5f;
					if (counter >= 1)
					{
						playerState.shieldDown = true;
					}
				}
				else {
					playerState.PlayerHP -= 1;
					playerState.InvincibilitySeconds = 1.5f;
				}
			}
		}

		vecToPlayer.Normalize();
		vecToPlayer *= -1.0f;
		currFoe.Position += vecToPlayer * FOE_MOVEMENT_SPEED * deltaSeconds;
	}

	Position = currFoe.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.85f);
	Visible = currFoe.Alive;
}








