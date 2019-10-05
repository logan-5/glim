#ifndef GLIM_EXAMPLE_WINDOW_SAMPLER_CONSUMER_HPP
#define GLIM_EXAMPLE_WINDOW_SAMPLER_CONSUMER_HPP

#include "sampler.hpp"

#include <memory>

class WindowSamplerConsumer : public glim::Sampler::Consumer {
   public:
    explicit WindowSamplerConsumer(glim::usize width, glim::usize height);
    ~WindowSamplerConsumer();

    void finishedChunk(const glim::Image& image,
                       glim::usize idx,
                       glim::usize size) override;

    void wait();

   private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif
