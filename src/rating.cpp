#include "rating.h"
#include "multistat.h"
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace wz::rating {
	inline namespace {
		void from_json(const nlohmann::json& json, rating& rating) {
			json.at("name").get_to(rating.name);
			json.at("elo").get_to(rating.elo);
			json.at("scale").get_to(rating.scale);
			json.at("rank").get_to(rating.rank);
			json.at("discounted").get_to(rating.discounted);
			json.at("spoiled").get_to(rating.spoiled);
			json.at("gameCount").get_to(rating.gameCount);
			json.at("winCount").get_to(rating.winCount);
			json.at("loseCount").get_to(rating.loseCount);
			json.at("drawCount").get_to(rating.drawCount);
			json.at("invalidGameCount").get_to(rating.invalidGameCount);
			json.at("lastSeenDays").get_to(rating.lastSeenDays);
			json.at("spanDays").get_to(rating.spanDays);
			json.at("farmElo").get_to(rating.farmElo);
			json.at("xFarmElo").get_to(rating.xFarmElo);
			json.at("powerWonVersusTeamRatio").get_to(rating.powerWonVersusTeamRatio);
			json.at("researchRatio").get_to(rating.researchRatio);
			json.at("quitTimeRatio").get_to(rating.quitTimeRatio);
		}
	}

	void apply_rating(std::uint32_t playerIndex) {
		static const char* const env = std::getenv("WARZONE2100_RATING_DATA_DIR");
		if (!env) return;
		static std::unordered_map<std::string, std::string> public_keys;
		static std::unordered_map<std::string, rating> elo;
		{ static bool loaded = false;
			if (!loaded) {
				loaded = true;
				debug(LOG_INFO, "rating env %s", env);
				const std::filesystem::path dir(env);
				nlohmann::json::parse(std::ifstream(dir / "player-public-keys.json")).get_to(public_keys);
				nlohmann::json::parse(std::ifstream(dir / "elo.json")).get_to(elo);
				for (auto& [key, value] : elo) value.publicKey = key;
			}
		}

		auto stats = getMultiStats(playerIndex);
		auto public_key = base64Encode(stats.identity.toBytes(EcKey::Privacy::Public));

		{ const auto it = public_keys.find(public_key);
			if (it != public_keys.end()) public_key = it->second;
		}

		{ const auto it = elo.find(public_key);
			if (it == elo.end()) stats.rating = {};
			else stats.rating = it->second;
		}

		debug(LOG_INFO, "rating %f %s %s", stats.rating.elo, public_key.c_str(), !stats.rating.name.empty() ? stats.rating.name.c_str() : NetPlay.players[playerIndex].name);

		if (NetPlay.isHost && !stats.rating.name.empty() && stats.rating.name != NetPlay.players[playerIndex].name)
			NETchangePlayerName(playerIndex, stats.rating.name.data());

		#if 0 // excerpt from lobbyplayerrow.cpp displayPlayer
			bool dummy = stat.played < 5;
			uint8_t star[3] = {0, 0, 0};
			uint8_t medal = 0;
			// star 1 total droid kills
			star[0] = stat.totalKills > 600? 1 : stat.totalKills > 300? 2 : stat.totalKills > 150? 3 : 0;
			// star 2 games played
			star[1] = stat.played > 200? 1 : stat.played > 100? 2 : stat.played > 50? 3 : 0;
			// star 3 games won.
			star[2] = stat.wins > 80? 1 : stat.wins > 40? 2 : stat.wins > 10? 3 : 0;
			// medals.
			medal = stat.wins >= 24 && stat.wins > 8 * stat.losses? 1 : stat.wins >= 12 && stat.wins > 4 * stat.losses? 2 : stat.wins >= 6 && stat.wins > 2 * stat.losses? 3 : 0;
		#endif
		if (stats.rating.discounted) {
			stats.played = 0;
			stats.wins = 0;
			stats.losses = 0;
			stats.totalKills = 0;
		} else {
			if (stats.rating.scale < 0.4) {
				if (stats.rating.scale < 0.1) stats.totalKills = 0;
				else if (stats.rating.scale < 0.2) stats.totalKills = 151;
				else if (stats.rating.scale < 0.3) stats.totalKills = 301;
				else stats.totalKills = 601;
				stats.played = 5;
				stats.wins = 10;
			} else {
				stats.totalKills = 601;
				if (stats.rating.scale < 0.7) {
					if (stats.rating.scale < 0.5) stats.played = 51;
					else if (stats.rating.scale < 0.6) stats.played = 101;
					else stats.played = 201;
					stats.wins = 10;
				} else {
					stats.played = 201;
					if (stats.rating.scale < 0.8) stats.wins = 11;
					else if (stats.rating.scale < 0.9) stats.wins = 41;
					else stats.wins = 81;
				}
			}
			if (stats.rating.rank > 6) stats.losses = stats.wins;
			else if (stats.rating.rank > 3) stats.losses = stats.wins / 2 - 1;
			else if (stats.rating.rank > 1) stats.losses = stats.wins / 4 - 1;
			else stats.losses = stats.wins / 8 - 1;
		}
	}
}
