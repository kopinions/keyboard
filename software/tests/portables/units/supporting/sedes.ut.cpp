#include "supporting/sedes.hpp"

int main() {
    std::vector<kopinions::key_t> keys{{kopinions::key_t::id_t::RALT, kopinions::key_t::status_t::PRESSED}};
    sedes *s = new sedes{};
    const std::unique_ptr<char[]> &ptr = s->serialize(keys);
    char *buf = ptr.get();
}
