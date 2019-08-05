#include <locale>
#include <iostream>
#include <streambuf>

class streambuf_uppercase_writer : public std::streambuf {
public:
    streambuf_uppercase_writer(std::ostream& sink) : sink_(sink) {};

private:
    int_type overflow(int_type ch) override;

private:
    std::ostream& sink_;
};


streambuf_uppercase_writer::int_type streambuf_uppercase_writer::overflow(int_type ch)
{
    if (ch != traits_type::eof()) {
        // convert lowercase to uppercase and write the character to output
        ch = std::toupper(static_cast<char>(ch), getloc());
        sink_.put(static_cast<char>(ch));

        if (sink_.eof())
            return traits_type::eof();
    }

    return traits_type::to_int_type(static_cast<char>(ch));
}


int main()
{
    streambuf_uppercase_writer uwsb(std::cout);
    std::ostream out(&uwsb);

    out << "dies ist ein test. ein kurzer satz. noch einer." << std::endl;
}
