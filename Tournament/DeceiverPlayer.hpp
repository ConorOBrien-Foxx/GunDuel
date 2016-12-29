// DeceiverPlayer by Sxntk
// PPCG: http://codegolf.stackexchange.com/a/104972/11933

// DeceiverPlayer.hpp
// If we have two shoots, better shoot one by one

#ifndef __DECEIVER_PLAYER_HPP__
#define __DECEIVER_PLAYER_HPP__

#include "Player.hpp"

class DeceiverPlayer final : public Player
{
public:
	DeceiverPlayer(size_t opponent = -1) : Player(opponent) {}

public:
	virtual Action fight()
	{
		int ammo = getAmmo();
		int opponentAmmo = getAmmoOpponent();
		int turn = getTurn();

		// Without ammo, always load
		if (ammo == 0)
		{
			return load();
		}

		// Every 10 turns the Deceiver goes crazy
		if (turn % 10)
		{
			// Generate random integer in [0, 5)
			int random = rand() % 5;
			switch (random)
			{
			case 0:
				return bullet();
			case 1:
				return metal();
			case 2:
				if (ammo == 1)
				{
					return bullet();
				}

				return plasma();
			case 3:
				return thermal();
			case 4:
				return load();
			}
		}

		// The Deceiver shoots one bullet
		if (ammo == 2)
		{
			return bullet();
		}

		// Protect until we can get bullet 2
		if (opponentAmmo == 0)
		{
			return load();
		}

		if (opponentAmmo == 1)
		{
			return metal();
		}

		if (opponentAmmo == 2)
		{
			return thermal();
		}
	}
};

#endif // !__DECEIVER_PLAYER_HPP__