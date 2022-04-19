#include <cstdint>
#include <cstdlib>
#include <hpx/local/algorithm.hpp>
#include <hpx/local/execution.hpp>
#include <hpx/local/init.hpp>


template<typename T>
class Matrix{
private:
    const std::uint32_t n, m;
    std::vector<T> mat;

public:
    Matrix (const std::uint32_t _n, const std::uint32_t _m) : n(_n), m(_m), mat(n*m, 0) {}
    Matrix (const std::vector<T> &_mat) : mat(_mat) {}
    Matrix (std::vector<T> &&_mat) : mat(std::move(_mat)) {}

    ~Matrix() = default;

    // Util funcs
    T &operator()(size_t i, size_t j){
        assert(i < n and j < m);
        return mat[i * m + j];
    }

    const T &operator()(size_t i, size_t j) const {
        assert(i < n and j < m);
        return mat[i * m + j];
    }

    std::pair<size_t, size_t> getDim(){
        return std::make_pair(n, m);
    }

    void randomize(std::uniform_int_distribution<T> dis, std::mt19937 gen){
        for(auto &i:mat) i = dis(gen);
    }

    // Binary op
    Matrix<T> operator * (const Matrix<T> &other){
        assert(m == other.n);
        Matrix<T> ret(n, other.m);
        hpx::for_loop(hpx::execution::par, 0, n, [&](auto i){
            hpx::for_loop(hpx::execution::par, 0, other.m, [&](auto j){
                hpx::for_loop(hpx::execution::seq, 0, m, [&](auto k){
                    ret(i, j) += mat[i * m + k] * other(k, j);
                });
            });
        });
        return ret;
    }

    // Input
    friend std::istream &operator>>(std::istream &in, Matrix &_mat){
        for(auto &i:_mat)
            in >> i;
        return in;
    }

    // Output - Pretty print
    friend std::ostream &operator<<(std::ostream &out, Matrix &_mat){
        // Lamba to quickly get width of number
        std::function<size_t(int)> num_len = [&](int n){
            if(n == 0) return static_cast<size_t>(1);
            if(n < 0) return static_cast<size_t>(1 + num_len(-n));
            return static_cast<size_t>(1 + num_len(n/10));
        };

        // Find max width number
        int _n, _m;
        std::tie(_n, _m) = _mat.getDim(); // Use structured binding C++17 onward
        std::vector<std::size_t> maxw_col(_m);
        for(size_t r=0; r<_n; r++)
            for(size_t c=0; c<_m; c++) maxw_col[c] = std::max(maxw_col[c], num_len(_mat(r, c)));

        // Pretty print
        for(size_t r=0; r<_n; r++)
            for(size_t c=0; c<_m; c++)
                std::cout << ((c==0) ? "| " : " ") << std::setw(maxw_col[c]) << _mat(r, c) << ((c==_m-1) ? " |\n" : " ");
        
        return out;
    }
};