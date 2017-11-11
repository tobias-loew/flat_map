namespace std {

struct sorted_unique_t { unspecified };
inline constexpr sorted_unique_t sorted_unique { unspecified };

template <class Key, class T, class Compare = less<Key>,
          class KeyContainer = vector<Key>,
          class MappedContainer = vector<T>>
class flat_map {
public:
    // types:
    using key_type                 = Key;
    using mapped_type              = T;
    using value_type               = pair<Key, T>;
    using key_compare              = Compare;
    using key_allocator_type       = typename KeyContainer::allocator_type;
    using mapped_allocator_type    = typename MappedContainer::allocator_type;
    using reference                = pair<const Key&, T&>;
    using const_reference          = pair<const Key&, const T&>;
    using size_type                = typename KeyContainer::size_type;
    using iterator                 = implementation-defined;
    using const_iterator           = implementation-defined;
    using reverse_iterator         = implementation-defined;
    using const_reverse_iterator   = implementation-defined;
    using key_container_type       = KeyContainer;
    using mapped_container_type    = MappedContainer;

    class value_compare {
      friend class flat_map;
    protected:
      Compare comp;
      value_compare(Compare c) : comp(c) { }
    public:
      bool operator()(const value_type& x, const value_type& y) const {
        return comp(x.first, y.first);
      }
    };

    // construct/copy/destroy:
    flat_map();
    flat_map(KeyContainer, MappedContainer);
    template <class Container>
      explicit flat_map(Container);
    template <class Container, class KeyAlloc, class MappedAlloc>
      flat_map(Container, const KeyAlloc&, const MappedAlloc&);

    explicit flat_map(const Compare& comp);
    template <class KeyAlloc, class MappedAlloc>
      flat_map(const Compare& comp, const KeyAlloc&, const MappedAlloc&);
    template <class KeyAlloc, class MappedAlloc>
      flat_map(const KeyAlloc&, const MappedAlloc&);

    template <class InputIterator>
      flat_map(InputIterator first, InputIterator last,
               const Compare& comp = Compare());
    template <class InputIterator, class KeyAlloc, class MappedAlloc>
      flat_map(InputIterator first, InputIterator last,
               const Compare& comp, const KeyAlloc&, const MappedAlloc&);
    template <class InputIterator, class KeyAlloc, class MappedAlloc>
      flat_map(InputIterator first, InputIterator last,
               const KeyAlloc& ka, const MappedAlloc& ma)
        : flat_map(first, last, Compare(), ka, ma) { }

    template <class InputIterator>
      flat_map(sorted_unique_t, InputIterator first, InputIterator last,
               const Compare& comp = Compare());
    template <class InputIterator, class KeyAlloc, class MappedAlloc>
      flat_map(sorted_unique_t, InputIterator first, InputIterator last,
               const Compare& comp, const KeyAlloc&, const MappedAlloc&);
    template <class InputIterator, class KeyAlloc, class MappedAlloc>
      flat_map(sorted_unique_t, InputIterator first, InputIterator last,
               const KeyAlloc& ka, const MappedAlloc& ma)
        : flat_map(first, last, Compare(), ka, ma) { }

    template <class KeyAlloc, class MappedAlloc>
      flat_map(const flat_map&, const KeyAlloc&, const MappedAlloc&);
    template <class KeyAlloc, class MappedAlloc>
      flat_map(flat_map&&, const KeyAlloc&, const MappedAlloc&);

    flat_map(initializer_list<pair<Key, T>>,
             const Compare& = Compare());
    template <class KeyAlloc, class MappedAlloc>
      flat_map(initializer_list<pair<Key, T>>,
               const Compare&,
               const KeyAlloc&, const MappedAlloc&);
    template <class KeyAlloc, class MappedAlloc>
      flat_map(initializer_list<pair<Key, T>> il,
               const KeyAlloc& ka, const MappedAlloc& ma)
        : flat_map(il, Compare(), ka, ma) { }
    flat_map& operator=(initializer_list<pair<Key, T>>);

    // iterators:
    iterator                 begin() noexcept;
    const_iterator           begin() const noexcept;
    iterator                 end() noexcept;
    const_iterator           end() const noexcept;

    reverse_iterator         rbegin() noexcept;
    const_reverse_iterator   rbegin() const noexcept;
    reverse_iterator         rend() noexcept;
    const_reverse_iterator   rend() const noexcept;

    const_iterator           cbegin() const noexcept;
    const_iterator           cend() const noexcept;
    const_reverse_iterator   crbegin() const noexcept;
    const_reverse_iterator   crend() const noexcept;

    // size:
    bool      empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;

    // element access:
    T& operator[](const key_type& x);
    T& operator[](key_type&& x);
    T& at(const key_type& x);
    const T& at(const key_type& x) const;

    // modifiers:
    template <class... Args> pair<iterator, bool> emplace(Args&&... args);
    template <class... Args> iterator emplace_hint(const_iterator position, Args&&... args);
    pair<iterator, bool> insert(const value_type& x);
    pair<iterator, bool> insert(value_type&& x);
    template <class P> pair<iterator, bool> insert(P&& x);
    iterator insert(const_iterator position, const value_type& x);
    iterator insert(const_iterator position, value_type&& x);
    template <class P>
      iterator insert(const_iterator position, P&&);
    template <class InputIterator>
      void insert(InputIterator first, InputIterator last);
    template <class InputIterator>
      void insert(sorted_unique_t, InputIterator first, InputIterator last);
    void insert(initializer_list<pair<Key, T>>);

    std::pair<KeyContainer, MappedContainer> extract() &&;
    void replace(KeyContainer&&, MappedContainer&&);

    template <class... Args>
      pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);
    template <class... Args>
      pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);
    template <class... Args>
      iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args);
    template <class... Args>
      iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);
    template <class M>
      pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
    template <class M>
      pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
    template <class M>
      iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);
    template <class M>
      iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);

    iterator erase(iterator position);
    iterator erase(const_iterator position);
    size_type erase(const key_type& x);
    iterator erase(const_iterator first, const_iterator last);

    void swap(flat_map& fm)
        noexcept(
            noexcept(declval<KeyContainer>().swap(declval<KeyContainer&>())) &&
            noexcept(declval<MappedContainer>().swap(declval<MappedContainer&>()))
        );
    void clear() noexcept;

    template<class C2>
    void merge(flat_map<Key, T, C2, KeyContainer, MappedContainer>& source);
    template<class C2>
      void merge(flat_map<Key, T, C2, KeyContainer, MappedContainer>&& source);
    template<class C2>
      void merge(flat_multimap<Key, T, C2, KeyContainer, MappedContainer>& source);
    template<class C2>
      void merge(flat_multimap<Key, T, C2, KeyContainer, MappedContainer>&& source);

    // observers:
    key_compare key_comp() const;
    value_compare value_comp() const;

    // map operations:
    iterator find(const key_type& x);
    const_iterator find(const key_type& x) const;
    template <class K> iterator find(const K& x);
    template <class K> const_iterator find(const K& x) const;

    size_type count(const key_type& x) const;
    template <class K> size_type count(const K& x) const;

    iterator lower_bound(const key_type& x);
    const_iterator lower_bound(const key_type& x) const;
    template <class K> iterator lower_bound(const K& x);
    template <class K> const_iterator lower_bound(const K& x) const;

    iterator upper_bound(const key_type& x);
    const_iterator upper_bound(const key_type& x) const;
    template <class K> iterator upper_bound(const K& x);
    template <class K> const_iterator upper_bound(const K& x) const;

    pair<iterator, iterator> equal_range(const key_type& x);
    pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
    template <class K>
      pair<iterator, iterator> equal_range(const K& x);
    template <class K>
      pair<const_iterator, const_iterator> equal_range(const K& x) const;
};

template <class Container>
  using cont_key_t = typename Container::value_type::first_type; // exposition only
template <class Container>
  using cont_val_t = typename Container::value_type::first_type; // exposition only

template <class Container>
  flat_map(Container)
    -> flat_map<cont_key_t<Container>, cont_val_t<Container>,
                less<cont_key_t<Container>>,
                std::vector<cont_key_t<Container>>,
                std::vector<cont_val_t<Container>>>;

template <class KeyContainer, class MappedContainer>
  flat_map(KeyContainer, MappedContainer)
    -> flat_map<typename KeyContainer::value_type,
                typename MappedContainer::value_type,
                less<typename KeyContainer::value_type>,
                KeyContainer, MappedContainer>;

template <class Container, class KeyAlloc, class MappedAlloc>
  flat_map(Container, KeyAlloc, MappedAlloc)
    -> flat_map<cont_key_t<Container>, cont_val_t<Container>,
                less<cont_key_t<Container>>,
                std::vector<cont_key_t<Container>>,
                std::vector<cont_val_t<Container>>>;

template <class KeyContainer, class MappedContainer,
          class KeyAlloc, class MappedAlloc>
  flat_map(KeyContainer, MappedContainer, KeyAlloc, MappedAlloc)
    -> flat_map<typename KeyContainer::value_type,
                typename MappedContainer::value_type,
                less<typename KeyContainer::value_type>,
                KeyContainer, MappedContainer>;

template<class Compare, class KeyAlloc, class MappedAlloc>
  flat_map(Compare, KeyAlloc, MappedAlloc)
    -> flat_map<alloc_key_t<KeyAlloc>, alloc_val_t<MappedAlloc>, Compare,
                std::vector<alloc_key_t<KeyAlloc>>,
                std::vector<alloc_val_t<MappedAlloc>>>;

template<class KeyAlloc, class MappedAlloc>
  flat_map(KeyAlloc, MappedAlloc)
    -> flat_map<alloc_key_t<KeyAlloc>, alloc_val_t<MappedAlloc>,
                less<alloc_key_t<KeyAlloc>>,
                std::vector<alloc_key_t<KeyAlloc>>,
                std::vector<alloc_val_t<MappedAlloc>>>;

template <class InputIterator, class Compare = less<iter_key_t<InputIterator>>>
  flat_map(InputIterator, InputIterator, Compare = Compare())
    -> flat_map<iter_key_t<InputIterator>, iter_val_t<InputIterator>,
                less<iter_key_t<InputIterator>>,
                std::vector<iter_key_t<InputIterator>>,
                std::vector<iter_val_t<InputIterator>>>;

template<class InputIterator, class Compare,
         class KeyAlloc, class MappedAlloc>
  flat_map(InputIterator, InputIterator, Compare, KeyAlloc, MappedAlloc)
    -> flat_map<iter_key_t<InputIterator>, iter_val_t<InputIterator>, Compare,
                std::vector<iter_key_t<InputIterator>>,
                std::vector<iter_val_t<InputIterator>>>;

template<class InputIterator, class KeyAlloc, class MappedAlloc>
  flat_map(InputIterator, InputIterator, KeyAlloc, MappedAlloc)
    -> flat_map<iter_key_t<InputIterator>, iter_val_t<InputIterator>,
                less<iter_key_t<InputIterator>>,
                std::vector<iter_key_t<InputIterator>>,
                std::vector<iter_val_t<InputIterator>>>;

template <class InputIterator, class Compare = less<iter_key_t<InputIterator>>>
  flat_map(sorted_unique_t, InputIterator, InputIterator,
           Compare = Compare())
    -> flat_map<iter_key_t<InputIterator>, iter_val_t<InputIterator>,
                less<iter_key_t<InputIterator>>,
                std::vector<iter_key_t<InputIterator>>,
                std::vector<iter_val_t<InputIterator>>>;

template<class InputIterator, class Compare,
         class KeyAlloc, class MappedAlloc>
  flat_map(sorted_unique_t, InputIterator, InputIterator,
           Compare, KeyAlloc, MappedAlloc)
    -> flat_map<iter_key_t<InputIterator>, iter_val_t<InputIterator>, Compare,
                std::vector<iter_key_t<InputIterator>>,
                std::vector<iter_val_t<InputIterator>>>;

template<class InputIterator, class KeyAlloc, class MappedAlloc>
  flat_map(sorted_unique_t, InputIterator, InputIterator,
           KeyAlloc, MappedAlloc)
    -> flat_map<iter_key_t<InputIterator>, iter_val_t<InputIterator>,
                less<iter_key_t<InputIterator>>,
                std::vector<iter_key_t<InputIterator>>,
                std::vector<iter_val_t<InputIterator>>>;

template<class Key, class T, class Compare = less<Key>>
  flat_map(initializer_list<pair<Key, T>>, Compare = Compare())
    -> flat_map<Key, T, Compare, vector<Key>, vector<T>>;

template<class Key, class T, class Compare, class KeyAlloc, class MappedAlloc>
  flat_map(initializer_list<pair<Key, T>>, Compare, KeyAlloc, MappedAlloc)
    -> flat_map<Key, T, Compare, vector<Key>, vector<T>>;

template<class Key, class T, class KeyAlloc, class MappedAlloc>
  flat_map(initializer_list<pair<Key, T>>, KeyAlloc, MappedAlloc)
    -> flat_map<Key, T, less<Key>, vector<Key>, vector<T>>;

// the comparisons below are for exposition only
template <class Key, class T, class Compare, class Container>
  bool operator==(const flat_map<Key, T, Compare, Container>& x,
                  const flat_map<Key, T, Compare, Container>& y);
template <class Key, class T, class Compare, class Container>
  bool operator< (const flat_map<Key, T, Compare, Container>& x,
                  const flat_map<Key, T, Compare, Container>& y);
template <class Key, class T, class Compare, class Container>
  bool operator!=(const flat_map<Key, T, Compare, Container>& x,
                  const flat_map<Key, T, Compare, Container>& y);
template <class Key, class T, class Compare, class Container>
  bool operator> (const flat_map<Key, T, Compare, Container>& x,
                  const flat_map<Key, T, Compare, Container>& y);
template <class Key, class T, class Compare, class Container>
  bool operator>=(const flat_map<Key, T, Compare, Container>& x,
                  const flat_map<Key, T, Compare, Container>& y);
template <class Key, class T, class Compare, class Container>
  bool operator<=(const flat_map<Key, T, Compare, Container>& x,
                  const flat_map<Key, T, Compare, Container>& y);

// specialized algorithms:
template <class Key, class T, class Compare, class Container>
  void swap(flat_map<Key, T, Compare, Container>& x,
            flat_map<Key, T, Compare, Container>& y)
    noexcept(noexcept(x.swap(y)));

}
