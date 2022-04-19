#include <hpx/local/execution.hpp>
#include <hpx/local/init.hpp>
#include <matrix.hpp>

int hpx_main(hpx::program_options::variables_map& vm) {

    std::size_t n = vm["n"].as<std::size_t>();
    std::size_t k = vm["k"].as<std::size_t>();
    std::size_t m = vm["m"].as<std::size_t>();
    std::int32_t l = vm["l"].as<std::int32_t>();
    std::int32_t r = vm["r"].as<std::int32_t>();
    assert(l <= r);

    Matrix<int> M1(n, k), M2(k, m);
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(l, r);
    M1.randomize(dis, gen);
    M2.randomize(dis, gen);
    Matrix<int> product = M1 * M2;
    std::cout << M1 << "*\n" << M2 << "=\n" << product;

    return hpx::local::finalize();
}

int main(int argc, char **argv) {
    using namespace hpx::program_options;

    options_description cmdline("usage: " HPX_APPLICATION_STRING " [options]");
    cmdline.add_options()
        ("n", hpx::program_options::value<std::size_t>()->default_value(2), "Rows of matrix 1")
        ("k", hpx::program_options::value<std::size_t>()->default_value(3), "Columns of matrix 1 / Rows of matrix 2")
        ("m", hpx::program_options::value<std::size_t>()->default_value(2), "Columns of matrix 2")
        ("l", hpx::program_options::value<std::int32_t>()->default_value(-5), "Lower bound on values")
        ("r", hpx::program_options::value<std::int32_t>()->default_value(5), "Upper bound on values");

    hpx::local::init_params init_args;
    init_args.desc_cmdline = cmdline;
    return hpx::local::init(hpx_main, argc, argv, init_args);
}