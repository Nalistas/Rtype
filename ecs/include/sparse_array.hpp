#ifndef SPARSE_ARRAY_HPP
#define SPARSE_ARRAY_HPP

#include <vector>
#include <optional>

template <typename Component>
class sparse_array {
public:
    // Types utilisés
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = value_type const&;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    // Constructors & destructors
    sparse_array();
    sparse_array(sparse_array const&);
    sparse_array(sparse_array&&) noexcept;
    ~sparse_array();

    // Operators
    sparse_array& operator=(sparse_array const&);
    sparse_array& operator=(sparse_array&&) noexcept;
    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;

    // Iterators
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    // Insertion
    size_type size() const;
    reference_type insert_at(size_type pos, Component const&);
    reference_type insert_at(size_type pos, Component&&);

    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params);


    // Suppression
    void erase(size_type pos);

    // Researching
    size_type get_index(value_type const&) const;

private:
    container_t _data;
    void ensure_size(size_type size);
};

// Inclusion des définitions de la classe template
#include "sparse_array.tpp"

#endif // SPARSE_ARRAY_HPP
