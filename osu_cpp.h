#pragma once
#include <curl/curl.h>
#include <json.hpp>
#include <cpr/cpr.h>

class osu_cpp {
public:

	class osuApiV2 {
	public:

		std::string authToken;
		std::string client_id;
		std::string client_secret;

		void Auth() {
			nlohmann::json AuthResult;
			std::string body = R"({"client_id":)" + client_id + R"(, "client_secret":")" + client_secret + R"(", "grant_type":"client_credentials", "scope":"public"})";
			auto r = cpr::Post(cpr::Url{ "https://osu.ppy.sh/oauth/token" },
				cpr::Body{
				body
				},
				cpr::Header{ { "Content-Type", "application/json" } });
			AuthResult = nlohmann::json::parse(r.text);
			authToken = "Bearer " + AuthResult.value("access_token", "");
		}
	};
};
