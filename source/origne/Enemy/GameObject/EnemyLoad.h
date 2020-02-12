#pragma once

#include "./LoadEnemyGameObject.h"
#include <array>
#include <Singleton.h>

#include <filesystem>
#include <fstream>
#include <iostream>

using fi = std::ifstream;

namespace fs = std::experimental::filesystem;

namespace mslib {
namespace loader {
class EnemyLoader:public pattern::Singleton<EnemyLoader>{
public:
	EnemyLoader() = default;
	~EnemyLoader() = default;

	const origin::game::EnemyStatus& Load(unsigned int _enemyNumber) {
		if (0 == m_enemyStatusDinamicArray.size()) {
			// ファイルを開く前処理
			fi file;
			fs::path filePath("enemy.csv");
			std::vector<std::string> str;
			std::string backStr;
			struct StrStatus {
				std::string fileName;
				std::string hp;
				std::string def;
				std::string spd;
				std::string sp;
			};
			std::vector<std::array<std::string, 5>> status;
			// ファイルを開く
			file.open(filePath, fi::out);

			// ファイルが開けているか
			if (file.fail())
			{
				// std::cerr << "失敗" << std::endl;
				return m_enemyStatusDinamicArray[0];
			}

			// 表のラインの文字列を保持
			while (getline(file, backStr)) {
				str.push_back(backStr);
				// std::cout << "[" << backStr << "]" << std::endl;
			}

			std::string::size_type pos = 0;
			status.resize(str.size());
			int i = 0;
			for (auto itr : str) {
				std::string::size_type first = 0;
				std::string::size_type end;
				std::string::size_type difference;
				int j = 0;
				do {
					pos = itr.find(',', first);
					end = pos;
					difference = end - first;
					auto ans = itr.substr(first, difference);
					// std::cout << ans << std::endl;
					status[i][j] = ans;
					first = end + 1;

					j++;
				} while (pos != std::string::npos);
				i++;
			}
			for (auto itr : status) {
				origin::game::EnemyStatus enemtStatus;

				enemtStatus.m_modelFilePaht = itr[0];
				enemtStatus.hp = atoi(itr[1].c_str());
				enemtStatus.def = atoi(itr[2].c_str());
				enemtStatus.spd = atoi(itr[3].c_str());
				enemtStatus.sp = atoi(itr[4].c_str());

				m_enemyStatusDinamicArray.push_back(enemtStatus);
			}	
		}
		return m_enemyStatusDinamicArray[_enemyNumber];
	}
private:
	std::vector<origin::game::EnemyStatus> m_enemyStatusDinamicArray;
};
}
}