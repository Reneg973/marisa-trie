#include "marisa/trie.h"

#include <memory>
#include <stdexcept>

#include "marisa/grimoire/trie.h"
#include "marisa/iostream.h"
#include "marisa/stdio.h"

namespace marisa {

Trie::Trie()
  : trie_(new grimoire::LoudsTrie) {
}

Trie::~Trie() = default;

Trie::Trie(Trie &&other) noexcept = default;

Trie &Trie::operator=(Trie &&other) noexcept = default;

void Trie::build(Keyset &keyset, int config_flags) {
  std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie(keyset, config_flags));
  trie_.swap(temp);
}

bool Trie::lookup(Agent &agent) const {
  return trie_->lookup(agent);
}

void Trie::reverse_lookup(Agent &agent) const {
  trie_->reverse_lookup(agent);
}

bool Trie::common_prefix_search(Agent &agent) const {
  return trie_->common_prefix_search(agent);
}

bool Trie::predictive_search(Agent &agent) const {
  return trie_->predictive_search(agent);
}

std::size_t Trie::num_tries() const {
  return trie_->num_tries();
}

std::size_t Trie::num_keys() const {
  return trie_->num_keys();
}

std::size_t Trie::num_nodes() const {
  return trie_->num_nodes();
}

TailMode Trie::tail_mode() const {
  return trie_->tail_mode();
}

NodeOrder Trie::node_order() const {
  return trie_->node_order();
}

bool Trie::empty() const {
  return trie_->empty();
}

std::size_t Trie::size() const {
  return trie_->size();
}

std::size_t Trie::total_size() const {
  return trie_->total_size();
}

std::size_t Trie::io_size() const {
  return trie_->io_size();
}

void Trie::clear() noexcept {
  Trie().swap(*this);
}

void Trie::swap(Trie &rhs) noexcept {
  trie_.swap(rhs.trie_);
}

}  // namespace marisa

#include <iostream>

namespace marisa {

class TrieIO {
 public:
  static void fread(std::FILE *file, Trie *trie) {
    MARISA_THROW_IF(trie == nullptr, std::invalid_argument);

    std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie);

    grimoire::Reader reader;
    reader.open(file);
    temp->read(reader);
    trie->trie_.swap(temp);
  }
  static void fwrite(std::FILE *file, const Trie &trie) {
    MARISA_THROW_IF(file == nullptr, std::invalid_argument);
    MARISA_THROW_IF(trie.trie_ == nullptr, std::logic_error);
    grimoire::Writer writer;
    writer.open(file);
    trie.trie_->write(writer);
  }

  static std::istream &read(std::istream &stream, Trie *trie) {
    MARISA_THROW_IF(trie == nullptr, std::invalid_argument);

    std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie);

    grimoire::Reader reader;
    reader.open(stream);
    temp->read(reader);
    trie->trie_.swap(temp);
    return stream;
  }
  static std::ostream &write(std::ostream &stream, const Trie &trie) {
    MARISA_THROW_IF(trie.trie_ == nullptr, std::logic_error);
    grimoire::Writer writer;
    writer.open(stream);
    trie.trie_->write(writer);
    return stream;
  }
};

void fread(std::FILE *file, Trie *trie) {
  MARISA_THROW_IF(file == nullptr, std::invalid_argument);
  MARISA_THROW_IF(trie == nullptr, std::invalid_argument);
  TrieIO::fread(file, trie);
}

void fwrite(std::FILE *file, const Trie &trie) {
  MARISA_THROW_IF(file == nullptr, std::invalid_argument);
  TrieIO::fwrite(file, trie);
}

std::istream &read(std::istream &stream, Trie *trie) {
  MARISA_THROW_IF(trie == nullptr, std::invalid_argument);
  return TrieIO::read(stream, trie);
}

std::ostream &write(std::ostream &stream, const Trie &trie) {
  return TrieIO::write(stream, trie);
}

std::istream &operator>>(std::istream &stream, Trie &trie) {
  return read(stream, &trie);
}

std::ostream &operator<<(std::ostream &stream, const Trie &trie) {
  return write(stream, trie);
}


void TrieSerializer::mmap(const char *filename, int flags) {
  MARISA_THROW_IF(filename == nullptr, std::invalid_argument);

  std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie);

  grimoire::Mapper mapper;
  mapper.open(filename, flags);
  temp->map(mapper);
  trie_.trie_.swap(temp);
}

void TrieSerializer::map(const void *ptr, std::size_t size) {
  MARISA_THROW_IF((ptr == nullptr) && (size != 0), std::invalid_argument);

  std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie);

  grimoire::Mapper mapper;
  mapper.open(ptr, size);
  temp->map(mapper);
  trie_.trie_.swap(temp);
}

void TrieSerializer::load(const char *filename) {
  MARISA_THROW_IF(filename == nullptr, std::invalid_argument);

  std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie);

  grimoire::Reader reader;
  reader.open(filename);
  temp->read(reader);
  trie_.trie_.swap(temp);
}

void TrieSerializer::read(int fd) {
  MARISA_THROW_IF(fd == -1, std::invalid_argument);

  std::unique_ptr<grimoire::LoudsTrie> temp(new grimoire::LoudsTrie);

  grimoire::Reader reader;
  reader.open(fd);
  temp->read(reader);
  trie_.trie_.swap(temp);
}

void TrieSerializer::save(const char *filename) const {
  MARISA_THROW_IF(trie_.trie_ == nullptr, std::logic_error);
  MARISA_THROW_IF(filename == nullptr, std::invalid_argument);

  grimoire::Writer writer;
  writer.open(filename);
  trie_.trie_->write(writer);
}

void TrieSerializer::write(int fd) const {
  MARISA_THROW_IF(trie_.trie_ == nullptr, std::logic_error);
  MARISA_THROW_IF(fd == -1, std::invalid_argument);

  grimoire::Writer writer;
  writer.open(fd);
  trie_.trie_->write(writer);
}


}  // namespace marisa
