#include "rating.h"
#include "multistat.h"
#include "urlrequest.h"
#include "lib/framework/wzapp.h"
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <chrono>
#include <mutex>
#include <optional>
#include <functional>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <physfs.h>

namespace wz::rating {
	inline namespace {
		void from_json(const nlohmann::json& json, rating& rating) {
			json.at("name").get_to(rating.name);
			json.at("elo").get_to(rating.elo);
			json.at("scale").get_to(rating.scale);
			json.at("rank").get_to(rating.rank);
			json.at("discounted").get_to(rating.discounted);
			json.at("spoiled").get_to(rating.spoiled);
			json.at("optedOut").get_to(rating.opted_out);
			json.at("gameCount").get_to(rating.game_count);
			json.at("winCount").get_to(rating.win_count);
			json.at("loseCount").get_to(rating.lose_count);
			json.at("drawCount").get_to(rating.draw_count);
			json.at("invalidGameCount").get_to(rating.invalid_game_count);
			json.at("lastSeenDays").get_to(rating.last_seen_days);
			json.at("spanDays").get_to(rating.span_days);
			json.at("farmElo").get_to(rating.farm_elo);
			json.at("xFarmElo").get_to(rating.x_farm_elo);
			json.at("powerWonVersusTeamRatio").get_to(rating.power_won_versus_team_ratio);
			json.at("researchRatio").get_to(rating.research_ratio);
			json.at("quitTimeRatio").get_to(rating.quit_time_ratio);
		}

		constexpr std::string_view default_url_ = "https://warzone2100.retropaganda.info";
		std::string url_(default_url_);

		std::mutex mutex;
		std::unordered_map<std::string, std::string> ips, public_keys;
		std::unordered_map<std::string, rating> elo;

		void download_async(const std::filesystem::path& dest_dir, const std::filesystem::path& sub_path, std::function<void (nlohmann::json&&)> callback) {
			const auto path = dest_dir / sub_path;
			auto last_modified_path = path; last_modified_path += ".last-modified";
			std::string last_modified;
			std::getline(std::ifstream(last_modified_path), last_modified);
			URLDataRequest request;
			request.url = url_; request.url += '/'; request.url += sub_path.generic_string();
			if (!last_modified.empty()) request.setRequestHeader("if-modified-since", last_modified);
			request.autoRetryStrategy = URLRequestAutoRetryStrategy::RetryAfter(std::chrono::seconds(5));
			request.onFailure = [=](const std::string& url, URLRequestFailureType type, std::shared_ptr<HTTPResponseDetails> transferDetails) {
				const auto message = fmt::format("rating download failed: {} {} {} {}",
					url.c_str(),
					to_string(type),
					transferDetails->getInternalResultDescription().c_str(),
					transferDetails->httpStatusCode()
				);
				wzAsyncExecOnMainThread([message = std::move(message)]{ debug(LOG_ERROR, "%s", message.c_str()); });
			};
			request.onResponse = [=](const std::string& url, const HTTPResponseDetails& responseDetails, const std::shared_ptr<MemoryStruct>& data) -> URLRequestHandlingBehavior {
				switch (responseDetails.httpStatusCode()) {
					case 200: // OK: body will have new json
					case 304: // Not Modified: body will be empty
						break;
					default:
						const auto message = fmt::format("rating download failed: {} {}", url.c_str(), responseDetails.httpStatusCode());
						wzAsyncExecOnMainThread([message = std::move(message)]{ debug(LOG_ERROR, "%s", message.c_str()); });
						return URLRequestHandlingBehavior::Done();
				}
				std::optional<nlohmann::json> json;
				try {
						if (data->size) json = nlohmann::json::parse(data->memory, data->memory + data->size);
						else json = nlohmann::json::parse(std::ifstream(path));
				} catch (const std::exception& e) {
					const auto message = fmt::format("rating parsing failed: {} {}", url.c_str(), e.what());
					wzAsyncExecOnMainThread([message = std::move(message)]{ debug(LOG_ERROR, "%s", message.c_str()); });
					return URLRequestHandlingBehavior::Done();
				}
				try { callback(std::move(json.value())); }
				catch (const std::exception& e) {
					const auto message = fmt::format("rating loading failed: {} {}", url.c_str(), e.what());
					wzAsyncExecOnMainThread([message = std::move(message)]{ debug(LOG_ERROR, "%s", message.c_str()); });
				}
				if (data->size) {
					std::ofstream(path).write(data->memory, data->size);
					if (std::string last_modified; responseDetails.getHeader("last-modified", last_modified))
						std::ofstream(last_modified_path).write(last_modified.data(), last_modified.size());
				}
				const auto message = fmt::format("rating async retrieval completed: {}", url.c_str());
				wzAsyncExecOnMainThread([message = std::move(message)]{ debug(LOG_INFO, "%s", message.c_str()); });
				return URLRequestHandlingBehavior::Done();
			};
			urlRequestData(request);
		}

		template<typename T>
		void download_async_to(const std::filesystem::path& dest_dir, const std::filesystem::path& sub_path, T& output) {
			download_async(dest_dir, sub_path, [&](nlohmann::json&& json) {
				T temp;
				json.get_to(temp);
				{ std::lock_guard l(mutex);
					output = std::move(temp);
				}
			});
		}
	}

	std::string_view default_url() { return default_url_; }
	std::string_view url() { return url_; }
	void url(std::string_view url__) { url_ = url__; }

	void load_async() {
		std::filesystem::path dir = PHYSFS_getWriteDir(); dir /= "cache";
		if (const auto ips_path = dir / "player-ips.json"; std::filesystem::exists(ips_path)) {
			if (NetPlay.isHost) {
				try { nlohmann::json::parse(std::ifstream(ips_path)).get_to(ips); }
				catch (const std::exception& e) { debug(LOG_ERROR, "rating loading failed: %s %s", ips_path.filename().generic_string().c_str(), e.what()); }
			}

			try { nlohmann::json::parse(std::ifstream(dir / "player-public-keys.json")).get_to(public_keys); }
			catch (const std::exception& e) { debug(LOG_ERROR, "rating loading failed: %s %s", "player-public-keys.json", e.what()); }

			try { nlohmann::json::parse(std::ifstream(dir / "elo.json")).get_to(elo); }
			catch (const std::exception& e) { debug(LOG_ERROR, "rating loading failed: %s %s", "elo.json", e.what()); }
		} else if (!url_.empty()) {
			debug(LOG_INFO, "rating url: %s", url_.c_str());
			download_async_to(dir, "player-public-keys.json", public_keys);
			download_async_to(dir, "elo.json", elo);
		}
	}

	void apply_rating(std::uint32_t playerIndex) {
		auto& stats = getMultiStats(playerIndex);

		{ std::lock_guard l(mutex);
			if(elo.empty()) return;

			auto public_key = base64Encode(stats.identity.toBytes(EcKey::Privacy::Public));

			{ const auto it = public_keys.find(public_key);
				if (it != public_keys.end()) public_key = it->second;
				else if (NetPlay.isHost) {
					const auto it2 = ips.find(NetPlay.players[playerIndex].IPtextAddress);
					if (it2 != ips.end()) public_key = it2->second;
				}
			}

			{ const auto it = elo.find(public_key);
				if (it == elo.end() || it->second.opted_out) stats.rating = {};
				else {
					stats.rating.public_key = it->first;
					static_cast<rating&>(stats.rating) = it->second;
				}
			}
		}

		if (NetPlay.isHost && !stats.rating.opted_out && !stats.rating.name.empty() && stats.rating.name != NetPlay.players[playerIndex].name)
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
