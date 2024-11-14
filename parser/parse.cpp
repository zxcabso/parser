#include "parse.h"

namespace parse
{
	namespace Csv {

		std::vector<Row> readCsv(std::string filename)
		{
			std::vector <parse::Csv::Row> rows;
			std::ifstream file(filename);
			std::string line;

			while (std::getline(file, line))
			{
				std::stringstream ss(line);
				std::string column;
				Row row;
				while (std::getline(ss, column, ','))
				{
					row.columns.push_back(column);
				}
				rows.push_back(row);
			}
			return rows;
		}
		void printCSV(const std::vector<Row>& rows) {
			for (const auto& row : rows) {
				for (size_t i = 0; i < row.columns.size(); ++i) {
					std::cout << row.columns[i];
					if (i < row.columns.size() - 1) {
						std::cout << ", ";
					}
				}
				std::cout << std::endl; 
			}
		}		
		void searchCSV(const std::vector<Row>& rows, const std::string& search) {
			bool found = false;

			for (const auto& row : rows) {
				for (const auto& column : row.columns) {
					if (column == search) {
						for (const auto& col : row.columns) {
							std::cout << col << " ";
						}
						std::cout << std::endl;
						found = true;
						break;
					}
				}
			}
			if (!found) {
				std::cout << search << "\" not found." << std::endl;
			}
		}
	}
}
