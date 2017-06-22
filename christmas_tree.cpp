#include <iostream>
#include <iomanip>
#include <random>

std::string tree_layer(unsigned int width, std::default_random_engine &rand_eng)
{
    std::uniform_int_distribution<int> random(0, 10);
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

void draw_tree(
        std::ostream &out,
        std::default_random_engine &rand_eng,
        int base_radius,
        int height,
        float branch_slope_ratio,
        int layers)
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
            << tree_layer(tree_width, rand_eng) << '\n';

        radius += slope;
        if (layer > branch_end) {
            radius -= int(0.5 + cut_in);
            branch_end += branch_height;
        }
    }
}

int main()
{
    const auto base_radius = 10;
    const auto height = 30;
    const auto branch_slope_ratio = 5.0f;
    const auto layers = 5;
    std::random_device r;
    std::default_random_engine rand_eng(r());

    draw_tree(std::cout, rand_eng, base_radius, height, branch_slope_ratio, layers);
    return 0;
}
