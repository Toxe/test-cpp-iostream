#include <iostream>
#include <streambuf>
#include <vector>
#include <cstdio>
#include <stdexcept>

class file_reader_streambuf : public std::streambuf {
public:
    explicit file_reader_streambuf(FILE* fp, std::size_t buffer_size=256, std::size_t put_back=8);

private:
    int_type underflow() override;

    // copy ctor and assignment not implemented; copying not allowed
    file_reader_streambuf(const file_reader_streambuf&);
    file_reader_streambuf& operator=(const file_reader_streambuf&);

private:
    FILE* fp_;
    const std::size_t put_back_;
    std::vector<char> buffer_;
};


file_reader_streambuf::file_reader_streambuf(FILE* fp, std::size_t buffer_size, std::size_t put_back) :
    fp_(fp),
    put_back_(std::max(put_back, std::size_t(1))),
    buffer_(std::max(buffer_size, put_back_) + put_back_)
{
    // Set the back, current and end buffer pointers to be equal.
    // This will force an underflow() on the first read and hence fill the buffer.
    char* end = &buffer_.front() + buffer_.size();
    setg(end, end, end);
}

std::streambuf::int_type file_reader_streambuf::underflow()
{
    if (gptr() < egptr())
        return traits_type::to_int_type(*gptr());

    char* base = &buffer_.front();
    char* start = base;

    if (eback() == base) {
        // make arrangements for putback characters
        std::memmove(base, egptr() - put_back_, put_back_);
        start += put_back_;
    }

    // start is now the start of the buffer, proper.
    // Read from fp_ in to the provided buffer.
    std::size_t n = std::fread(start, 1, buffer_.size() - (start - base), fp_);

    if (n == 0)
        return traits_type::eof();

    // set buffer pointers
    setg(base, start, start + n);

    return traits_type::to_int_type(*gptr());
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <text file>" << std::endl;
        return 1;
    }

    FILE* fp = std::fopen(argv[1], "r");

    if (!fp)
        throw std::runtime_error{"failed to open " + std::string{argv[1]}};

    file_reader_streambuf frsb(fp, 1);
    std::istream in(&frsb);
    std::string s;

    while (in >> s)
        std::cout << "WORD: " << s << std::endl;

//    while (std::getline(in, s))
//        std::cout << "LINE: " << s << std::endl;

    std::fclose(fp);
}
