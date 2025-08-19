#pragma once
#include <memory>

namespace Roguelike {
/**
 * @brief Interface for objects that can save and load their state using the
Memento pattern.
 * @tparam T The derived class type that implements this interface (using CRTP).
 * @tparam Y The memento class type used to store state data.
 *
 * @details This template class provides a consistent API for save/load
operations while
 * enforcing that derived classes implement the actual save|load logic through
 * SaveImpl() and LoadImpl() methods. This follows the Curiously Recurring
Template
 * Pattern (CRTP) for static polymorphism.
 *
 * @note Derived classes must implement:
 *   - void SaveImpl(std::shared_ptr<Y> save) const
 *   - void LoadImpl(std::shared_ptr<const Y> save)
 *
 * @example
 * class MySave { int data; };
 * class MyClass : public ISaveable<MyClass, MySave> {
 * private:
 *   friend class ISaveable<MyClass, MySave>;
 *   void SaveImpl(std::shared_ptr<MySave> save) const { ... };
 *   void LoadImpl(std::shared_ptr<const MySave> save) { ... };
};
*/
template <class T, class Y>
class ISaveable {
   public:
    /**
     * @brief Creates a new save object with the current state.
     * @return std::shared_ptr<Y> A shared pointer to the newly created save
     * object.
     *
     * @details This is a convenience method that creates the save object
     * internally and populates it with the current state by calling
     * Save(std::shared_ptr<Y>).
     */
    std::shared_ptr<Y> Save() const {
        std::shared_ptr<Y> save = std::make_shared<Y>();
        Save(save);
        return save;
    };
    /**
     * @brief Saves the current state to an existing save object.
     * @param save A shared pointer to the save object to populate.
     *
     * @details This method allows reusing save objects to avoid unnecessary
     * allocations. The actual serialization logic is implemented in the derived
     * class's SaveImpl() method.
     */
    void Save(std::shared_ptr<Y> save) const {
        static_cast<const T*>(this)->SaveImpl(save);
    };
    /**
     * @brief Loads state from a save object.
     * @param save A shared pointer to a constant save object containing the
     * state to load.
     *
     * @details The save object is treated as read-only during the loading
     * process. The actual deserialization logic is implemented in the derived
     * class's LoadImpl() method.
     */
    void Load(std::shared_ptr<const Y> save) {
        static_cast<T*>(this)->LoadImpl(save);
    };
};
}  // namespace Roguelike
