#ifndef MARISA_GRIMOIRE_TRIE_CONFIG_H_
#define MARISA_GRIMOIRE_TRIE_CONFIG_H_

#include <stdexcept>

#include "marisa/base.h"

namespace marisa::grimoire::trie {

class Config {
 public:
  Config() = default;
  explicit Config(int flags) {
    parse(flags);
  }
  Config(const Config &) = delete;
  Config &operator=(const Config &) = delete;

  void parse(int config_flags) {
    MARISA_THROW_IF((config_flags & ~MARISA_CONFIG_MASK) != 0,
                    std::invalid_argument);

    parse_num_tries(config_flags);
    parse_cache_level(config_flags);
    parse_tail_mode(config_flags);
    parse_node_order(config_flags);
  }

  int flags() const {
    return flags_;
  }

  std::size_t num_tries() const {
    return static_cast<std::size_t>(flags_ & MARISA_NUM_TRIES_MASK);
  }
  CacheLevel cache_level() const {
    return static_cast<CacheLevel>(flags_ & MARISA_CACHE_LEVEL_MASK);
  }
  TailMode tail_mode() const {
    return static_cast<TailMode>(flags_ & MARISA_TAIL_MODE_MASK);
  }
  NodeOrder node_order() const {
    return static_cast<NodeOrder>(flags_ & MARISA_NODE_ORDER_MASK);
  }

  void clear() noexcept {
    Config().swap(*this);
  }
  void swap(Config &rhs) noexcept {
    std::swap(flags_, rhs.flags_);
  }

 private:
  int flags_ = MARISA_DEFAULT_NUM_TRIES | MARISA_DEFAULT_CACHE
        | MARISA_DEFAULT_TAIL | MARISA_DEFAULT_ORDER;

  void parse_num_tries(int config_flags) {
  }

  void parse_cache_level(int config_flags) {
    switch (config_flags & MARISA_CACHE_LEVEL_MASK) {
      case 0: {
        flags_ |= MARISA_DEFAULT_CACHE;
        break;
      }
      case MARISA_HUGE_CACHE: {
        break;
      }
      case MARISA_LARGE_CACHE: {
        break;
      }
      case MARISA_NORMAL_CACHE: {
        break;
      }
      case MARISA_SMALL_CACHE: {
        break;
      }
      case MARISA_TINY_CACHE: {
        break;
      }
      default: {
        MARISA_THROW(std::invalid_argument, "undefined cache level");
      }
    }
  }

  void parse_tail_mode(int config_flags) {
    switch (config_flags & MARISA_TAIL_MODE_MASK) {
      case 0: {
        flags_ |= MARISA_DEFAULT_TAIL;
        break;
      }
      case MARISA_TEXT_TAIL: {
        break;
      }
      case MARISA_BINARY_TAIL: {
        break;
      }
      default: {
        MARISA_THROW(std::invalid_argument, "undefined tail mode");
      }
    }
  }

  void parse_node_order(int config_flags) {
    switch (config_flags & MARISA_NODE_ORDER_MASK) {
      case 0: {
        flags_ |= MARISA_DEFAULT_ORDER;
        break;
      }
      case MARISA_LABEL_ORDER: {
        break;
      }
      case MARISA_WEIGHT_ORDER: {
        break;
      }
      default: {
        MARISA_THROW(std::invalid_argument, "undefined node order");
      }
    }
  }
};

}  // namespace marisa::grimoire::trie

#endif  // MARISA_GRIMOIRE_TRIE_CONFIG_H_
