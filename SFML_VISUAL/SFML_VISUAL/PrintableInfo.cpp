#include <vector>
#include <sstream>

template <class T>
class PrintableInfo
{
	public:
		PrintableInfo() {};

		std::vector<T*> data;
		std::vector<std::string> dataName;
		std::ostringstream out;

		void addInfo(std::string id, T& x)
		{
			dataName.push_back(id);
			data.push_back(&x);
		}

		std::string str()
		{
			out.str("");
			out.clear();
			out << "---PRINTABLE INFO---" << std::endl;
			for (int i = 0; i < (int)data.size(); i++)
			{
				out << dataName.at(i) << ": " << *data.at(i) << std::endl;
			}

			return out.str();
		}


};