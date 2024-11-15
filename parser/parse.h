#pragma once
#include <iostream>
#include <fstream>
#include <sstream> 
#include <vector>
#include <string>
#include <unordered_map>

namespace parse
{
	namespace Csv
	{
		struct Row { std::vector<std::string> columns; };

		std::vector<Row> readCsv(std::string filename);
		void printCSV(const std::vector<Row>& rows);
		void searchCSV(const std::vector<Row>& rows, const std::string& search);
	}
	namespace Txt
	{
		std::vector<std::string> readTXT(const std::string& filename);
		void printTXT(const std::vector<std::string>& lines);
		void searchTXT(const std::vector<std::string>& lines, const std::string& searchTerm);
	}
	namespace xml
	{
		struct xml {
			std::string name; 
			std::string text;
			std::unordered_map<std::string, std::string> attributes; 
			std::vector<xml> children;

			void addChild(const xml& child) {
				children.push_back(child);
			}
		};
		std::unordered_map<std::string, std::string> parseAttributes(const std::string& line);
		xml parseXML(std::ifstream& file);
		void printXML(const xml& node, int depth);
	}
	namespace html
	{
		struct htmlNode {
			std::string name;
			std::unordered_map<std::string, std::string> attributes; 
			std::string text;
			std::vector < htmlNode > children;

			void addChild(const htmlNode & child) {
				children.push_back(child);
			}
		};

		std::unordered_map<std::string, std::string> parseAttributes(const std::string& line);
		htmlNode parseHTML(std::ifstream& file);
		void printHTML(const htmlNode& node, int depth = 0);
	}

}