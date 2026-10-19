#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include <filesystem>

namespace wz::rating {

	struct rating {
		std::string name;
		unsigned int rank = 0, game_count = 0, win_count = 0, lose_count = 0, draw_count = 0, invalid_game_count = 0, last_seen_days = 0, span_days = 0;
		float elo = 0, scale = 0, farm_elo = 0, x_farm_elo = 0, power_won_versus_team_ratio = 0, research_ratio = 0, quit_time_ratio = 0;
		bool discounted = true, spoiled = false;
	};

	std::string_view default_url();
	std::string_view url();
	void url(std::string_view url);
	void load_async();
	void apply_rating(std::uint32_t playerIndex);
}
