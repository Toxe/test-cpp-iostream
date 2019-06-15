#include <iostream>
#include <streambuf>
#include <vector>
#include <cassert>
#include <functional>

class array_reader_streambuf : public std::streambuf {
public:
    array_reader_streambuf(const char* begin, const char* end);
    explicit array_reader_streambuf(const char* str);

private:
    int_type uflow() override;
    int_type underflow() override;
    int_type pbackfail(int_type ch) override;
    std::streamsize showmanyc() override;

private:
    const char* const begin_;
    const char* const end_;
    const char* current_;
};


array_reader_streambuf::array_reader_streambuf(const char* begin, const char* end) :
    begin_(begin),
    end_(end),
    current_(begin_)
{
    assert(std::less_equal<const char *>()(begin_, end_));
}

array_reader_streambuf::array_reader_streambuf(const char* str) :
    begin_(str),
    end_(begin_ + std::strlen(str)),
    current_(begin_)
{
}

array_reader_streambuf::int_type array_reader_streambuf::underflow()
{
    if (current_ == end_)
        return traits_type::eof();

    return traits_type::to_int_type(*current_);
}

array_reader_streambuf::int_type array_reader_streambuf::uflow()
{
    if (current_ == end_)
        return traits_type::eof();

    return traits_type::to_int_type(*current_++);
}

array_reader_streambuf::int_type array_reader_streambuf::pbackfail(int_type ch)
{
    if (current_ == begin_ || (ch != traits_type::eof() && ch != current_[-1]))
        return traits_type::eof();

    return traits_type::to_int_type(*--current_);
}

std::streamsize array_reader_streambuf::showmanyc()
{
    assert(std::less_equal<const char *>()(current_, end_));
    return end_ - current_;
}


int main()
{
    const char* text = "Dies ist ein String.";
    array_reader_streambuf arsb(text);

    std::istream in(&arsb);
    std::string s;

    while (in >> s)
        std::cout << "--> " << s << std::endl;

    in.clear();

    for (int i=0; i<3; ++i)
        in.unget();

    while (in >> s)
        std::cout << "==> " << s << std::endl;
}
