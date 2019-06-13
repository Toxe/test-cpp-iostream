#include <string>
#include <vector>
#include <fstream>

int main()
{
    std::vector<std::string> tokens{"first line", "second line", "third line"};
    std::ofstream out("fstream_simple_write.txt");

    for (auto s : tokens)
        out << s << "\n";

    out.close();
}
