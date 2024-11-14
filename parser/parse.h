#pragma once
#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>

namespace parse
{
	namespace Csv
	{
		struct Row { std::vector<std::string> columns; };

		std::vector<Row> readCsv(std::string filename);
		void printCSV(const std::vector<Row>& rows);
		void searchCSV(const std::vector<Row>& rows, const std::string& search);
	}
}