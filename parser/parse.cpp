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
	namespace Txt
	{
		std::vector<std::string> readTXT(const std::string& filename)
		{
			std::vector<std::string> lines;
			std::ifstream file(filename);

			if (!file.is_open()) {
				std::cerr << "Cannot open this file!" << std::endl;
				return lines;
			}

			std::string line;
			while (std::getline(file, line)) {
				lines.push_back(line);
			}

			file.close();
			return lines;
		}
		void printTXT(const std::vector<std::string>& lines)
		{
			for (const auto& line : lines) {
				std::cout << line << std::endl;
			}
		}
		void searchTXT(const std::vector<std::string>& lines, const std::string& searchTerm)
		{
			bool found = false;

			for (const auto& line : lines) {
				if (line.find(searchTerm) != std::string::npos) {
					std::cout << line << std::endl;
					found = true;
				}
			}

			if (!found) {
				std::cout << "String '" << searchTerm << "' not found." << std::endl;
			}
		}
	}
	namespace xml
	{
		std::unordered_map<std::string, std::string> parseAttributes(const std::string& line) {
			std::unordered_map<std::string, std::string> attributes;
			size_t pos = 0;

			while ((pos = line.find("=", pos)) != std::string::npos) {
				size_t start = line.rfind(' ', pos) + 1;
				std::string name = line.substr(start, pos - start);

				pos += 2;
				size_t end = line.find('"', pos);
				std::string value = line.substr(pos, end - pos);
				attributes[name] = value;

				pos = end + 1;
			}
			return attributes;
		}
		std::string extractText(const std::string& line, const std::string& openTag, const std::string& closeTag) {
			size_t start = line.find(openTag);
			size_t end = line.find(closeTag, start);
			if (start != std::string::npos && end != std::string::npos) {
				start += openTag.size();
				return line.substr(start, end - start);
			}
			return "";
		}
		xml parseXML(std::ifstream& file) {
			xml node;
			std::string line;

			while (std::getline(file, line)) {
				if (line.find('<') != std::string::npos && line.find("</") == std::string::npos) {
					size_t start = line.find('<') + 1;
					size_t end = line.find(' ', start);
					if (end == std::string::npos) end = line.find('>');

					node.name = line.substr(start, end - start);
					node.attributes = parseAttributes(line);

					size_t textStart = line.find('>') + 1;
					size_t textEnd = line.find("</", textStart);
					if (textEnd != std::string::npos) {
						node.text = line.substr(textStart, textEnd - textStart);
					}
					else {
						while (true) {
							xml childNode = parseXML(file);
							if (childNode.name.empty()) break;
							node.addChild(childNode);
						}
					}
				}
				else if (line.find("</") != std::string::npos) {
					break;
				}
			}
			return node;
		}
		void printXML(const xml& node, int depth = 0) {
			std::string indent(depth * 2, ' ');

			std::cout << indent << "<" << node.name;

			for (const auto& [key, value] : node.attributes) {
				std::cout << " " << key << "=\"" << value << "\"";
			}

			if (node.text.empty() && node.children.empty()) {
				std::cout << " />";
			}
			else {
				std::cout << ">";
				if (!node.text.empty()) {
					std::cout << node.text;
				}

				for (const auto& child : node.children) {
					std::cout << std::endl;
					printXML(child, depth + 1);
				}

				std::cout << indent << "</" << node.name << ">";
			}

			std::cout << std::endl;
		}
	}
		namespace html
		{
			std::unordered_map<std::string, std::string> parseAttributes(const std::string& line)
			{
				std::unordered_map<std::string, std::string> attributes;
				size_t pos = 0;

				while ((pos = line.find("=", pos)) != std::string::npos) {
					size_t start = line.rfind(' ', pos) + 1;
					std::string name = line.substr(start, pos - start);

					pos += 2;
					size_t end = line.find('"', pos);
					std::string value = line.substr(pos, end - pos);
					attributes[name] = value;

					pos = end + 1;
				}

				return attributes;
			}
			parse::html::htmlNode parseHTML(std::ifstream& file)
			{
				parse::html::htmlNode node;
				std::string line;

				while (std::getline(file, line)) {
					line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

					if (line.find('<') != std::string::npos && line.find("</") == std::string::npos) {
						size_t start = line.find('<') + 1;
						size_t end = line.find(' ', start);
						if (end == std::string::npos) end = line.find('>');

						node.name = line.substr(start, end - start);
						node.attributes = parseAttributes(line);

						size_t textStart = line.find('>') + 1;
						size_t textEnd = line.find("</", textStart);
						if (textEnd != std::string::npos) {
							node.text = line.substr(textStart, textEnd - textStart);
						}
						else {
							while (true) {
								parse::html::htmlNode childNode = parseHTML(file);
								if (childNode.name.empty()) break;
								node.addChild(childNode);
							}
						}
					}
					else if (line.find("</") != std::string::npos) {
						break;
					}
				}

				return node;
			}
			void html::printHTML(const parse::html::htmlNode& node, int depth) {
				std::string indent(depth * 2, ' ');
				std::cout << indent << "<" << node.name;

				for (const auto& [key, value] : node.attributes) {
					std::cout << " " << key << "=\"" << value << "\"";
				}

				if (node.children.empty() && node.text.empty()) {
					std::cout << " />\n";
				}
				else {
					std::cout << ">" << node.text << "\n";
					for (const auto& child : node.children) {
						html::printHTML(child, depth + 1);
					}
					std::cout << indent << "</" << node.name << ">\n";
				}
			}
		}
	}
