// Tournament.hpp
// Pitches Players against each other in a last-player-out gun duel tournament.

#ifndef __TOURNAMENT_HPP__
#define __TOURNAMENT_HPP__

// Tournament Core
#include "GunDuel.hpp"

// Necessary classes
#include <iostream>
#include <iomanip>
#include <memory>
#include <regex>
#include <algorithm>
#include <limits>
#include <numeric>
#include <chrono>
#include <random>
#include <typeinfo>

// Class responsible for a tournament.
template <class Pool>
class Tournament final
{
public:
	// Scorecard for a player.
	struct ScoreCard
	{
		// Unique player identifier.
		size_t identifier;
		// Is player still alive?
		bool alive;
		// Points in current round;
		int point;
		// Points in current round;
		int pointTotal;
		// How many rounds has the player survived?
		size_t survival;
		// How many points has the player gained in each round?
		std::vector<int> history;
	};

public:
	// Initializes a tournament.
	Tournament(size_t repetition = 100)
		: mSize(Pool::size()), mRepetition(repetition), mScores(mSize)
	{
		// Randomly assign identifier.
		std::vector<size_t> identifiers(mSize);
		std::iota(identifiers.begin(), identifiers.end(), 0);
		unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(identifiers.begin(), identifiers.end(), std::default_random_engine(seed));

		// Initialize players.
		for (size_t index = 0; index < mSize; ++index)
		{
			ScoreCard &sc = mScores[index];
			sc.identifier = identifiers[index];
			sc.alive = true;
			sc.point = 0;
			sc.pointTotal = 0;
			sc.survival = 0;
		}
	}

public:
	// Run the tournament!
	void run()
	{
		size_t round = 0;
		while (getPlayerRemaining() > 1)
		{
			startRound();
			for (size_t turn = 0; turn < mRepetition; ++turn)
			{
				for (size_t indexA = 0; indexA < mSize - 1; ++indexA)
				{
					if (!mScores[indexA].alive) continue;
					for (size_t indexB = indexA + 1; indexB < mSize; ++indexB)
					{
						if (!mScores[indexB].alive) continue;
						performDuel(indexA, indexB);
					}
				}
			}
			endRound();
			printScore();
		}
		printScoreBoard();
	}

private:

	// Perform a duel.
	void performDuel(size_t a, size_t b)
	{
		size_t identifierA = mScores[a].identifier;
		size_t identifierB = mScores[b].identifier;
		std::unique_ptr<Player> playerA = Pool::newPlayer(a, identifierB);
		std::unique_ptr<Player> playerB = Pool::newPlayer(b, identifierA);
		GunDuel duel(*playerA, *playerB);
		GunDuel::Outcome status = duel.fight();
		switch (status)
		{
		case GunDuel::AWIN:
			mScores[a].point += 1;
			mScores[a].pointTotal += 1;
			break;
		case GunDuel::BWIN:
			mScores[b].point += 1;
			mScores[b].pointTotal += 1;
			break;
		}
	}

	// Declare the start of a round.
	void startRound()
	{
		// Set all points to zero.
		std::for_each(mScores.begin(), mScores.end(), [](ScoreCard &sc) -> void {
			sc.point = 0;
		});
	}

	// Declare the end of a round.
	void endRound()
	{
		// Get the minimum score.
		int minPoint = std::numeric_limits<int>::max();
		std::for_each(mScores.begin(), mScores.end(), [&](ScoreCard const &sc) -> void {
			if (sc.alive && sc.point < minPoint)
				minPoint = sc.point;
		});

		int minPointTotal = std::numeric_limits<int>::max();
		std::for_each(mScores.begin(), mScores.end(), [&](ScoreCard &sc) -> void {
			if (!sc.alive) return;
			// Only loop through players that are alive.
			if (sc.point > minPoint)
			{
				// Advance player to next round.
				sc.history.push_back(sc.point);
				sc.survival++;
			}
			else if (sc.pointTotal < minPointTotal)
			{
				minPointTotal = sc.pointTotal;
			}
		});

		std::for_each(mScores.begin(), mScores.end(), [&](ScoreCard &sc) -> void {
			if (!sc.alive || sc.point > minPoint) return;
			// Only loop through tied players.
			if (sc.pointTotal > minPointTotal)
			{
				// Advance tied player to next round.
				sc.history.push_back(sc.point);
				sc.survival++;
			}
			else
			{
				// Remove player from tournament.
				sc.alive = false;
			}
		});
	}

private:
	// Get the number of remaining players
	size_t getPlayerRemaining() const
	{
		return std::count_if(mScores.begin(), mScores.end(), [](ScoreCard const &s) -> bool {
			return s.alive;
		});
	}

	// Print score.
	void printScore() const
	{
		std::cout << " :: ScoreBoard" << std::endl;
		size_t index = 0;
		std::for_each(mScores.begin(), mScores.end(), [&index](ScoreCard const &sc) -> void {
			std::cout << "    " << std::setw(2) << (index++) << " ";
			if (sc.alive)
				std::cout << "ALIVE";
			else
				std::cout << "-----";
			std::cout << " " << std::setw(6) << sc.point << "/" 
				<< std::setw(6) << sc.pointTotal
				<< " " << sc.survival << std::endl;
		});
	}

	// Print scoreboard.
	void printScoreBoard() const
	{
		std::regex classRegex("(?:.*) (.*)$");

		int scoreboardLink = 4;

		std::vector<std::string> lines;
		for (size_t index = 0; index < mSize; ++index)
		{
			ScoreCard const &sc = mScores[index];

			std::string classDecl(typeid(*Pool::newPlayer(index)).name());
			std::string className;
			std::smatch classMatch;

			if (std::regex_search(classDecl, classMatch, classRegex))
				className = classMatch[1];
			else
				className = classDecl;

			// | [Class][Lnk] | Language | Survival | Points |
			std::stringstream sst;
			sst << " | " << std::setw(40) << std::left << std::string("[") + className + "][" + std::to_string(scoreboardLink++) + "]"
				<< " | " << std::setw(10) << "C++"
				<< " | " << std::setw(2) << std::right << sc.survival << " round"
				<< (sc.survival == 1 ? " " : "s")
				<< " | " << std::setw(6) << std::right << sc.pointTotal
				<< " |";
			lines.push_back(sst.str());
		}

		// Sort by survival
		std::vector<size_t> indices(mSize);
		std::iota(indices.begin(), indices.end(), 0);
		std::vector<ScoreCard> const &scores = mScores;
		std::sort(indices.begin(), indices.end(), [scores](size_t a, size_t b) -> bool {
			return scores[a].survival > scores[b].survival
				|| scores[a].survival == scores[b].survival && scores[a].pointTotal > scores[b].pointTotal;
		});

		// Prints table for README.md
		std::cout << " :: Final Scoreboard\n\n"
			<< " | Player                                   | Language   | Survival  | Points |\n"
			<< " |:---------------------------------------- |:---------- | ---------:| ------:|\n";
		for (size_t index : indices)
			std::cout << lines[index] << "\n";
		std::cout << std::endl;
	}

private:
	// Size of tournament.
	const size_t mSize;

	// Number of duel between every two players in each round of tournament.
	size_t mRepetition;

	// Keeps track of the scoreboard.
	std::vector<ScoreCard> mScores;
};

#endif // ! __TOURNAMENT_HPP__