#include <iostream>
#include <vector>
#include <concepts>
#include <algorithm>

// 1. Описываем контракт стратегии
template<typename T>
concept CompressionStrategy = requires(T s, const std::vector<char>& data) {
    { s.compress(data) } -> std::same_as<void>;
};

// 2. Конкретные реализации
struct ZipCompression {
    void compress(const std::vector<char>& data) const { 
        std::cout << "Using ZIP compression\n"; 
    }
};

struct RleCompression {
    void compress(const std::vector<char>& data) const { 
        std::cout << "Using RLE compression\n"; 
    }
};

// 3. Контекст (использует статический полиморфизм)
template<CompressionStrategy Strategy>
class Archiver {
    Strategy strategy;
public:
    void createArchive(const std::vector<char>& data) {
        strategy.compress(data);
    }
};

int main() {
    Archiver<ZipCompression> zipArchiver;
    zipArchiver.createArchive({'a', 'b', 'c'});

    Archiver<RleCompression> rleArchiver;
    rleArchiver.createArchive({'x', 'y'});
}
