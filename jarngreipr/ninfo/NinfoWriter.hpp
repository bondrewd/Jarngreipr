#ifndef JARNGREIPR_NINFO_WRITER_HPP
#define JARNGREIPR_NINFO_WRITER_HPP
#include <jarngreipr/ninfo/NinfoData.hpp>
#include <jarngreipr/io/write_error.hpp>
#include <fstream>
#include <iomanip>

namespace jarngreipr
{

template<typename realT>
class NinfoWriter
{
  public:
    using real_type = realT;
    using data_type = NinfoData<real_type>;

  public:

    explicit NinfoWriter(const std::string& fname)
        : filename_(fname), ofstrm_(fname)
    {
        if(!ofstrm_.good())
        {
            write_error(std::cerr, "NinfoReader: file open error: ", filename_);
            std::exit(EXIT_FAILURE);
        }
    }

    template<std::size_t Nu, std::size_t Np, std::size_t Nc, NinfoKind kind>
    void write_block(
        const std::vector<NinfoElement<real_type, Nu, Np, Nc, kind>>& block)
    {
        using ninfo_type = NinfoElement<real_type, Nu, Np, Nc, kind>;

        this->ofstrm_ << "<<<< " << ninfo_type::prefix << '\n';
        for(const auto& ninfo : block)
        {
            this->ofstrm_ << ninfo_type::prefix << ' ';
            for(auto& unit  : ninfo.units)
            {
                this->ofstrm_ << std::setw(6) << std::right << unit << ' ';
            }
            for(auto& imp   : ninfo.imps)
            {
                this->ofstrm_ << std::setw(6) << std::right << imp << ' ';
            }
            for(auto& impun : ninfo.impuns)
            {
                this->ofstrm_ << std::setw(6) << std::right << impun << ' ';
            }
            for(auto& coef  : ninfo.coefs)
            {
                this->ofstrm_ << std::setw(9) << std::setprecision(4)
                              << std::fixed << std::showpoint << std::right
                              << coef << ' ';
            }
            this->ofstrm_ << ninfo.suffix << '\n';
        }
        this->ofstrm_ << ">>>>\n";
        return;
    }

  private:

    std::string filename_;
    std::ofstream ofstrm_;
};

} // jarngreipr
#endif// JARNGREIPR_NINFO_READER_HPP
