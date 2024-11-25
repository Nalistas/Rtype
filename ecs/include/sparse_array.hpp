#ifndef SPARSE_ARRAY_HPP
#define SPARSE_ARRAY_HPP

#include <vector>
#include <optional>

template <typename Component>
class sparse_array {
public:
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    //      Used types
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////

    /**
     * @brief The type of a component
    */
    using value_type = std::optional<Component>;

    /**
     * @brief The type of a reference to a component
     */
    using reference_type = value_type&;

    /**
     * @brief The type of a const reference to a component
    */
    using const_reference_type = value_type const&;

    /**
     * @brief The type of the container
     */
    using container_t = std::vector<value_type>;

    /**
     * @brief The type of the size
     */
    using size_type = typename container_t::size_type;

    /**
     * @brief The type of the iterator
     */
    using iterator = typename container_t::iterator;

    /**
     * @brief The type of the const iterator
     */
    using const_iterator = typename container_t::const_iterator;





    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    //      Constructors & destructors
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////

    /**
     * @brief Default constructor
     */
    sparse_array();

    /**
     * @brief Copy constructor
     * @param other the sparse array to copy
     */
    sparse_array(sparse_array const &other);

    /**
     * @brief Move constructor
     * @param other the sparse array to move
     * @note This constructor is noexcept
     */
    sparse_array(sparse_array &&other) noexcept;

    /**
     * @brief Default destructor
     */
    ~sparse_array();





    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    //      Operators
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////

    /**
     * @brief Assignment operator
     * @param other the sparse array to copy
     * @return a reference to the sparse array
     */
    sparse_array& operator=(sparse_array const&);

    /**
     * @brief Move assignment operator
     * @param other the sparse array to move
     * @return a reference to the sparse array
     */
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
