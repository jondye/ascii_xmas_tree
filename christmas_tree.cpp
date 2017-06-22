#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

/// Returns a std::string containing one layer of the tree including decoration.
///
/// \param decoration percentage of tree that has decoration (on averge).
/// \param width Width of the tree layer.
/// \param rand_eng Random number engine.
std::string tree_layer(
        int decoration,
        unsigned int width,
        std::default_random_engine &rand_eng)
{
    decoration = std::max(1, std::min(100, decoration)); // Clamp value to range 1-100
    const auto upper_bound = 200 / decoration - 1;
    std::uniform_int_distribution<int> random(0, upper_bound);
    std::string layer(width, '*');
    for (auto & x : layer) {
        switch (random(rand_eng)) {
            case 0:
                x = '.';
                break;
            case 1:
                x = 'o';
                break;
            default:
                break;
        }
    }
    return layer;
}

/// Draws an ascii christmas tree.
///
/// \param out The ostream object to output the ascii tree to
/// \param rand_eng Random number engine.
/// \param base_radius Radius of the tree at the widest base.
/// \param height Height of the tree.
/// \param branch_slope_ratio Ratio of branch slope to overall tree slope.
/// \param layers Number of layers in the tree (i.e. branches)
/// \param decoration Percentage of tree that has decoration (on averge).
void draw_tree(
        std::ostream &out,
        std::default_random_engine &rand_eng,
        int base_radius,
        int height,
        float branch_slope_ratio,
        int layers,
        int decoration)
{
    const auto average_slope = float(base_radius)/height;
    const auto slope = average_slope * branch_slope_ratio;
    const auto branch_height = float(height) / layers;
    const auto cut_in = branch_height * (slope - average_slope);

    auto radius = 0.0f;
    auto branch_end = branch_height;
    for (auto layer = 0; layer <= height; ++layer) {
        const auto int_radius = int(0.5 + radius);
        const auto tree_width = 1 + 2 * int_radius;
        const auto space_width = cut_in + base_radius - int_radius;

        out << std::string(space_width, ' ')
            << tree_layer(decoration, tree_width, rand_eng) << '\n';

        radius += slope;
        if (layer > branch_end) {
            radius -= int(0.5 + cut_in);
            branch_end += branch_height;
        }
    }
}

int main(int argc, char * argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("height", po::value<int>()->default_value(30), "height of the tree")
        ("width", po::value<int>()->default_value(20), "width of the tree")
        ("layers", po::value<int>()->default_value(5), "number of layers of branches")
        ("slope", po::value<float>()->default_value(5.0f), "how slopey branches are (higher is more horizontal)")
        ("decoration", po::value<int>()->default_value(20), "percent of tree that is decorated");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << '\n';
        return 1;
    }

    const auto base_radius = (vm["width"].as<int>() - 1) / 2;
    const auto height = vm["height"].as<int>();
    const auto layers = vm["layers"].as<int>();
    const auto branch_slope_ratio = vm["slope"].as<float>();
    const auto decoration = vm["decoration"].as<int>();

    std::random_device r;
    std::default_random_engine rand_eng(r());

    draw_tree(std::cout, rand_eng, base_radius, height, branch_slope_ratio, layers, decoration);
    return 0;
}
