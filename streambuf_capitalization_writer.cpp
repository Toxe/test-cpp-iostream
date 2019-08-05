#include <cctype>
#include <iostream>
#include <streambuf>
#include <vector>
#include <functional>
#include <cassert>

class capitalization_writer_streambuf : public std::streambuf {
public:
    explicit capitalization_writer_streambuf(std::ostream& sink, std::size_t buffer_size=256);

protected:
    bool capitalize_and_flush();

private:
    int_type overflow(int_type ch) override;
    int sync() override;

    // copy ctor and assignment not implemented; copying not allowed
    capitalization_writer_streambuf(const capitalization_writer_streambuf&);
    capitalization_writer_streambuf& operator=(const capitalization_writer_streambuf&);

private:
    bool cap_next_;
    std::ostream& sink_;
    std::vector<char> buffer_;
};


capitalization_writer_streambuf::capitalization_writer_streambuf(std::ostream& sink, std::size_t buffer_size) :
    cap_next_(true),
    sink_(sink),
    buffer_(buffer_size+1)
{
    sink_.clear();
    char* base = &buffer_.front();
    setp(base, base + buffer_.size() - 1);
}

capitalization_writer_streambuf::int_type capitalization_writer_streambuf::overflow(int_type ch)
{
    if (sink_ && ch != traits_type::eof()) {
        assert(std::less_equal<char*>()(pptr(), epptr()));
        *pptr() = char(ch);
        pbump(1);

        if (capitalize_and_flush())
            return ch;
    }

    return traits_type::eof();
}

int capitalization_writer_streambuf::sync()
{
    return capitalize_and_flush() ? 0 : -1;
}

bool capitalization_writer_streambuf::capitalize_and_flush()
{
    for (char *p=pbase(), *e=pptr(); p!=e; ++p) {
        if (*p == '.') {
            cap_next_ = true;
        } else if (std::isalpha(*p)) {
            if (cap_next_)
                *p = char(std::toupper(*p));

            cap_next_ = false;
        }
    }

    std::ptrdiff_t n = pptr() - pbase();
    pbump(static_cast<int>(-n));

    return bool(sink_.write(pbase(), n));
}


int main()
{
    capitalization_writer_streambuf cwsb(std::cout);
    std::ostream out(&cwsb);

    out << "dies ist ein test. ein kurzer satz. noch einer." << std::endl;
}
