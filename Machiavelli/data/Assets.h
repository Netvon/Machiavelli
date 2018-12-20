#pragma once

namespace data::assets {

	template<typename T>
	bool try_load_asset_into(const std::string& path, T& into)
	{
		std::ifstream stream(path);

		if (!stream.is_open()) {
			return false;
		}

		try
		{
			stream >> into;
			stream.close();

			return true;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what();
		}

		stream.close();
		return false;
	}
}