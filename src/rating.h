#pragma once
#include <cstdint>
#include <string>

namespace wz::rating {

	struct rating {
		std::string publicKey, name;
		unsigned int rank = 0, gameCount = 0, winCount = 0, loseCount = 0, drawCount = 0, invalidGameCount = 0, lastSeenDays = 0, spanDays = 0;
		float elo = 0, scale = 0, farmElo = 0, xFarmElo = 0, powerWonVersusTeamRatio = 0, researchRatio = 0, quitTimeRatio = 0;
		bool discounted = true, spoiled = false;
	};

	void apply_rating(std::uint32_t playerIndex);
}
