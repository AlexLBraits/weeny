#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <functional>
#include <unordered_map>

template<class T>
class Hierarchy
{
    friend class iterator_impl;
private:
    static unsigned int __id;
    static std::unordered_map<unsigned int, T*> __idReestr;

private:
    unsigned int _id;
    T* _parent;
    T* _next;
    T* _previous;
    T* _firstChild;
    T* _lastChild;
    int _childrenCount;

public:
    void (*_whenAnItemIsAdded)(T*);
    void (*_whenAnItemIsRemoved)(T*);

private:
    ///
    /// \brief _is_above - проверяет принадлежит ли нод иерархии
    /// \param node
    /// \return
    ///
    int _is_above (T* node) const
    {
        int step = 0;
        while (node)
        {
            node = node->_parent;
            ++step;
            if (node == this) return step;
        }
        return 0;
    }
    ///
    /// \brief _is_left_of
    /// \param node
    /// \return
    ///
    int _is_left_of (T* node) const
    {
        int step = 0;
        while (node)
        {
            node = node->_previous;
            ++step;
            if (node == this) return step;
        }
        return 0;
    }
    ///
    /// \brief _is_right_of
    /// \param node
    /// \return
    ///
    int _is_right_of (T* node) const
    {
        int step = 0;
        while (node)
        {
            node = node->_next;
            ++step;
            if (node == this) return step;
        }
        return 0;
    }
    ///
    /// \brief __childCanBeRemoved - проверяет можно ли извлечь нод из иерархии
    /// \param node
    /// \return
    ///
    bool __childCanBeRemoved(T* node) const
    {
        return node && node->_parent && node->_parent == this;
    }
    ///
    /// \brief __removeChild - извлекает нод из иерархии родителя без
    /// дополнительных проверок
    /// \param node
    /// \return
    ///
    T* __removeChild(T* node)
    {
        ///////////////////////////////////////////////////////////////
        /// прямой алгоритм
        if (_firstChild == node) _firstChild = node->_next;
        if (_lastChild == node) _lastChild = node->_previous;
        if (node->_next) node->_next->_previous = node->_previous;
        if (node->_previous) node->_previous->_next = node->_next;

        node->_parent = 0;
        node->_next = 0;
        node->_previous = 0;

        --_childrenCount;

        return node;
    }
    ///
    /// \brief _removeChild - извлекает нод из иерархии родителя после
    /// положительной проверки
    /// \param node - нод, который нужно извлечь
    /// \return - возвращает указатель на извлеченный нод
    /// или 0, если что то пошло не так
    ///
    T* _removeChild(T* node)
    {
        if (__childCanBeRemoved(node)) return __removeChild(node);
        return 0;
    }

public:
    ///
    /// \brief Hierarchy
    ///
    Hierarchy()
        : _id(++__id),
          _parent(0),
          _next(0),
          _previous(0),
          _firstChild(0),
          _lastChild(0),
          _childrenCount(0),
          _whenAnItemIsAdded(0),
          _whenAnItemIsRemoved(0)
    {
        __idReestr[_id] = (T*)this;
    }
    ///
    /// \brief Hierarchy
    /// \param v
    ///
    Hierarchy(const Hierarchy& v)
        : Hierarchy()
    {
        _whenAnItemIsAdded = v._whenAnItemIsAdded;
        _whenAnItemIsRemoved = v._whenAnItemIsRemoved;

        for(auto& c : v) appendChild(new T(c));
    }
    ///
    ///  \brief ~Hierarchy
    ///
    virtual ~Hierarchy()
    {
        clearChilds();
        __idReestr.erase(_id);
    }
    ///
    /// \brief operator =
    /// \param v
    /// \return
    ///
    Hierarchy& operator=(const Hierarchy& v)
    {
        clearChilds();
        for(auto& c : v) appendChild(new T(c));
    }
    ///
    /// \brief id
    /// \return
    ///
    unsigned int id() const
    {
        return _id;
    }
    ///
    /// \brief getObjecById
    /// \param id
    /// \return
    ///
    static T* getObjecById(unsigned int id)
    {
        auto res = __idReestr.find(id);
        if (res != __idReestr.end()) return res->second;
        return 0;
    }
    ///
    /// \brief firstChild - returns the first child of an element
    /// \param isNotSuitable
    /// \return
    ///
    T* firstChild() const
    {
        return _firstChild;
    }
    ///
    /// \brief lastChild - returns the last child of an element
    /// \param isNotSuitable
    /// \return
    ///
    T* lastChild() const
    {
        return _lastChild;
    }
    ///
    /// \brief nextSibling - returns the next node at the same node tree level
    /// \param isNotSuitable
    /// \return
    ///
    T* nextSibling() const
    {
        return _next;
    }
    ///
    /// \brief previousSibling - returns the previous element at the same node
    /// tree level
    ///
    /// \param isNotSuitable
    /// \return
    ///
    T* previousSibling() const
    {
        return _previous;
    }
    ///
    /// \brief parentNode
    /// \return
    ///
    T* parentNode() const
    {
        return _parent;    // Returns the parent node of an element
    }
    ///
    /// \brief root
    /// \return
    ///
    T* root() const
    {
        T* bp = (T*)this;
        while (bp->_parent) bp = bp->_parent;
        return bp;
    }
    ///
    /// \brief hasChildNodes - returns true if an element has any child nodes,
    /// otherwise false
    ///
    /// \param isNotSuitable
    /// \return
    ///
    bool hasChildNodes() const
    {
        return firstChild() != nullptr;
    }
    ///
    /// \brief childrenCount
    /// \return
    ///
    int childrenCount() const
    {
        return _childrenCount;
    }
    ///
    /// \brief appendChild - Adds a new child node, to an element, as the last
    /// child node
    ///
    /// \param newNode
    /// \return
    ///
    T* appendChild(T* newNode)
    {
        /// нельзя добавить нод, которого нет
        if (newNode == 0) return 0;
        /// нельзя добавить себе в качестве ребёнка собственного родителя или
        /// самого себя
        if (newNode == (T*)this) return 0;
        if (newNode->_is_above((T*)this)) return 0;
        /// нод уже имеет хозяина, но удалить его из списка детей не удалось
        if (newNode->_parent && newNode->_parent->removeChild(newNode) == 0)
        {
            return 0;
        }

        ///////////////////////////////////////////////////////////////////////
        // прямой алгоритм
        //
        newNode->_parent = (T*)this;
        newNode->_next = 0;
        newNode->_previous = _lastChild;

        if (_firstChild == 0)
        {
            _firstChild = _lastChild = newNode;
        }
        else
        {
            _lastChild->_next = newNode;
            _lastChild = newNode;
        }

        ++_childrenCount;

        if(_whenAnItemIsAdded) _whenAnItemIsAdded(newNode);

        return newNode;
    }
    ///
    /// \brief insertBefore - inserts a new child node before a specified,
    /// existing, child node
    ///
    /// \param newNode
    /// \param existingNode
    /// \return
    ///
    T* insertBefore(T* newNode, T* existingNode = 0)
    {
        /// если второй аргумент не указан, или не является нашим ребёнком
        /// то insertBefore превращается в appendChild
        if (
            existingNode == 0 ||
            existingNode->_parent == 0 ||
            existingNode->_parent != this
        )
        {
            return appendChild(newNode);
        }
        /// нельзя вставить нод, которого нет
        if (newNode == 0) return 0;
        /// нельзя добавить себе в качестве ребёнка собственного родителя или
        /// самого себя
        if (newNode->own((T*)this)) return 0;
        /// нод уже имеет хозяина, но удалить его из списка детей не удалось
        if (newNode->_parent && newNode->_parent->removeChild(newNode) == 0)
        {
            return 0;
        }

        ///////////////////////////////////////////////////////////////////////
        /// прямой алгоритм
        ///
        newNode->_parent = (T*)this;
        newNode->_next = existingNode;
        newNode->_previous = existingNode->_previous;
        existingNode->_previous = newNode;

        if (_firstChild == existingNode)
        {
            _firstChild = newNode;
        }
        else
        {
            newNode->_previous->_next = newNode;
        }

        ++_childrenCount;

        ((T*)this)->whenAnItemIsAdded(newNode);

        return newNode;
    }
    ///
    /// \brief removeChild - removes a child node from an element
    /// \param node
    /// \return
    ///
    T* removeChild(T* node)
    {
        if (__childCanBeRemoved(node))
        {
            if(_whenAnItemIsRemoved) _whenAnItemIsRemoved(node);
            return __removeChild(node);
        }
        return 0;
    }
    ///
    /// \brief clearChilds
    ///
    void clearChilds()
    {
        while (_firstChild)
        {
            T* p = _removeChild(_firstChild);
            if (p) delete p;
        }
    }
    ///
    /// \brief replaceChild - replaces a child node in an element
    /// \param newNode
    /// \param oldNode
    /// \return
    ///
    T* replaceChild(T* newNode, T* oldNode)
    {
        /// нельзя заменить нод, которого нет или который нам не принадлежит
        if (oldNode == 0 || oldNode->_parent == 0 || oldNode->_parent != this)
        {
            return 0;
        }
        /// нельзя вставить нод, которого нет
        if (newNode == 0) return 0;
        /// нельзя добавить себе в качестве ребёнка собственного родителя или
        /// самого себя
        if (newNode->own((T*)this)) return 0;
        /// нод уже имеет хозяина, но удалить его из списка детей не удалось
        if (newNode->_parent && newNode->_parent->removeChild(newNode) == 0)
        {
            return 0;
        }
        ///////////////////////////////////////////////////////////////////////
        /// прямой алгоритм
        if (_firstChild == oldNode) _firstChild = newNode;
        if (_lastChild == oldNode) _lastChild = newNode;

        newNode->_parent = oldNode->_parent;
        newNode->_next = oldNode->_next;
        newNode->_previous = oldNode->_previous;

        oldNode->_parent = 0;
        oldNode->_next = 0;
        newNode->_previous = 0;

        ((T*)this)->whenAnItemIsAdded(newNode);

        return oldNode;
    }
    ///
    /// \brief swap - swap a child node in an element
    /// \param node
    ///
    void swap(T* node)
    {
        if (node == 0) return;

        T* pf1 = _parent->_firstChild;
        T* pl1 = _parent->_lastChild;
        T* pf2 = node->_parent->_firstChild;
        T* pl2 = node->_parent->_lastChild;

        if (pf1 == this) _parent->_firstChild = node;
        if (pl1 == this) _parent->_lastChild = node;
        if (pf2 == node) node->_parent->_firstChild = (T*)this;
        if (pl2 == node) node->_parent->_lastChild = (T*)this;
        std::swap(this->_parent, node->_parent);

        if (_next) _next->_previous = node;
        if (node->_next) node->_next->_previous = (T*)this;
        std::swap(this->_next, node->_next);

        if (_previous) _previous->_next = node;
        if (node->_previous) node->_previous->_next = (T*)this;
        std::swap(this->_previous, node->_previous);
    }
    ///
    /// \brief childNodeAt
    /// \param n
    /// \return
    ///
    T* childNodeAt(int n)
    {
        if (n < 0 || n > _childrenCount) return 0;
        int i = 0;
        T* p = _firstChild;
        while (i != n)
        {
            i++;
            p = p->_next;
        }
        return p;
    }

    ////////////////////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ///
    template<typename U>
    class iterator_impl : public std::iterator<std::forward_iterator_tag, U>
    {
    public:
        iterator_impl() = default;

        explicit iterator_impl(U* container, U* pos)
            : m_container(container), m_pos(pos)
        {
        }
        iterator_impl(const iterator_impl& v)
            : m_container(v.m_container), m_pos(v.m_pos)
        {
        }
        iterator_impl& operator=(const iterator_impl& v)
        {
            m_container = v.m_container;
            m_pos = v.m_pos;
            return *this;
        }
        U& operator*() const
        {
            return *m_pos;
        }
        U* operator->() const
        {
            return m_pos;
        }
        bool operator==(const iterator_impl& v) const
        {
            return (m_container == v.m_container) && (m_pos == v.m_pos);
        }
        bool operator!=(const iterator_impl& v) const
        {
            return (m_container != v.m_container) || (m_pos != v.m_pos);
        }
        iterator_impl& operator++()
        {
            if(m_pos) m_pos = m_pos->nextSibling();
            return *this;
        }
    private:
        U* m_container;
        U* m_pos;
    };
    ////////////////////////////////////////////////////////////////////////////
    ///
    ///
    ///
    ///
    template<typename U>
    class reverse_iterator_impl : public std::iterator<std::forward_iterator_tag, U>
    {
    public:
        reverse_iterator_impl() = default;

        explicit reverse_iterator_impl(U* container, U* pos)
            : m_container(container), m_pos(pos)
        {
        }
        reverse_iterator_impl(const reverse_iterator_impl& v)
            : m_container(v.m_container), m_pos(v.m_pos)
        {
        }
        reverse_iterator_impl& operator=(const reverse_iterator_impl& v)
        {
            m_container = v.m_container;
            m_pos = v.m_pos;
            return *this;
        }
        U& operator*() const
        {
            return *m_pos;
        }
        U* operator->() const
        {
            return m_pos;
        }
        bool operator==(const reverse_iterator_impl& v) const
        {
            return (m_container == v.m_container) && (m_pos == v.m_pos);
        }
        bool operator!=(const reverse_iterator_impl& v) const
        {
            return (m_container != v.m_container) || (m_pos != v.m_pos);
        }
        reverse_iterator_impl& operator++()
        {
            if(m_pos) m_pos = m_pos->previousSibling();
            return *this;
        }
    private:
        U* m_container;
        U* m_pos;
    };


    using iterator = iterator_impl<T>;
    using const_iterator = iterator_impl<const T>;
    using reverse_iterator = reverse_iterator_impl<T>;
    using const_reverse_iterator = reverse_iterator_impl<const T>;

    iterator begin()
    {
        return iterator((T*)this, this->firstChild());
    }
    iterator end()
    {
        return iterator((T*)this, 0);
    }
    const_iterator begin() const
    {
        return const_iterator((T*)this, this->firstChild());
    }
    const_iterator end() const
    {
        return const_iterator((T*)this, 0);
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator((T*)this, this->lastChild());
    }
    reverse_iterator rend()
    {
        return reverse_iterator((T*)this, 0);
    }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator((T*)this, this->lastChild());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator((T*)this, 0);
    }
};

template<class T> unsigned int Hierarchy<T>::__id = 0;
template<class T> std::unordered_map<unsigned int, T*> Hierarchy<T>::__idReestr;

#endif /* HIERARCHY_H */
