#include "WindowSamplerConsumer.hpp"

#include "image.hpp"

#include <SFML/Graphics.hpp>

#include <mutex>

using glim::usize;

struct WindowSamplerConsumer::Impl {
    explicit Impl(usize width, usize height)
        : window{sf::VideoMode{static_cast<unsigned>(width),
                               static_cast<unsigned>(height)},
                 "glim render"} {
        usize size = width * height;
        std::vector<sf::Uint8> texData(size * 4);
        for (std::size_t i = 0; i < size; ++i) {
            texData[0u + i * 4u] = 0x7F;
            texData[1u + i * 4u] = 0x7F;
            texData[2u + i * 4u] = 0x7F;
            texData[3u + i * 4u] = 0xFF;
        }
        sf::Image screenImage;
        screenImage.create(width, height, texData.data());
        screenTexture.loadFromImage(screenImage);
        screenSprite.setTexture(screenTexture);
    }
    sf::RenderWindow window;
    sf::Texture screenTexture;
    sf::Sprite screenSprite;
    std::mutex screenTextureMutex;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
};

WindowSamplerConsumer::WindowSamplerConsumer(usize width, usize height)
    : impl{std::make_unique<Impl>(width, height)} {}
WindowSamplerConsumer::~WindowSamplerConsumer() = default;

namespace {
std::array<sf::Uint8, 4> asBytes(const glim::Color4 c) {
    return {{
          static_cast<sf::Uint8>(c.r() * 255.99f),
          static_cast<sf::Uint8>(c.g() * 255.99f),
          static_cast<sf::Uint8>(c.b() * 255.99f),
          static_cast<sf::Uint8>(c.a() * 255.99f),
    }};
}
}  // namespace

void WindowSamplerConsumer::finishedChunk(const glim::Image& image,
                                          const usize idx,
                                          const usize chunkSize) {
    const auto startingC = idx % image.getWidth();
    const auto startingR = idx / image.getWidth();
    struct Chunk {
        usize start, end;
        usize r;
    };
    std::vector<Chunk> chunks;
    {
        const auto rows = image.getHeight();
        for (usize chunk = chunkSize, i = startingR; chunk > 0 && i < rows;
             ++i) {
			const auto start = i > startingR ? 0 : startingC;
            chunks.push_back({start,
                              std::min(image.getWidth(), start + chunk), i});
            chunk -= chunks.back().end - chunks.back().start;
        }
    }
    for (auto& chunk : chunks) {
        const auto size = chunk.end - chunk.start;
        std::vector<sf::Uint8> pixels(size * 4);
        const auto start = chunk.start + chunk.r * image.getWidth();
        const auto end = chunk.end + chunk.r * image.getWidth();
        for (usize i = start; i < end; ++i) {
            const auto color = asBytes(image[i]);
            std::copy_n(color.data(), 4,
                        std::next(pixels.begin(), (i - start) * 4));
        }
        std::lock_guard<std::mutex> l{impl->screenTextureMutex};
        impl->screenTexture.update(pixels.data(), size, 1, chunk.start,
                                   chunk.r);
    }
}

void WindowSamplerConsumer::wait() {
    while (impl->window.isOpen()) {
        impl->processEvents();
    }
}

void WindowSamplerConsumer::loop() {
    while (impl->window.isOpen()) {
        impl->processEvents();
        impl->window.clear();
        {
            std::lock_guard<std::mutex> l{impl->screenTextureMutex};
            impl->window.draw(impl->screenSprite);
        }
        impl->window.display();
    }
}
