#pragma once
#include <memory>
#include <unordered_map>
#include <utility>

#include "SFML/Window/Event.hpp"

namespace MaxrEngine {
/**
 * @brief Singleton class responsible for polling and accessing SFML events.
 * @detail Singleton class responsible for SFML events. Have methods to poll
 * events from window and access to last captured events.
 */
class EventSystem {
   public:
    using ConstIterator = std::unordered_multimap<sf::Event::EventType,
                                                  sf::Event>::const_iterator;
    /**
     * @brief Returns singleton instance of EventSystem.
     * @return instance of EventSystem.
     */
    static std::shared_ptr<EventSystem> Instance();
    /**
     * @brief Polls and updates the internal list of SFML events from the main
     * window.
     */
    void UpdateSfEvents();
    /**
     * @brief Returns all SFML events captured in the last update, grouped by
     * event type.
     * @return events captured in the last update.
     */
    const std::unordered_multimap<sf::Event::EventType, sf::Event>&
    GetSfEvents() const;
    /**
     * @brief Returns events captured in the last update of specified type
     * @param type - type of event to return
     * @return std::pair containing a pair of iterators defining captured events
     * of type. If there are no such elements, past-the-end (see end())
     * iterators are returned as both elements of the pair.
     */
    std::pair<ConstIterator, ConstIterator> GetSfEvents(
        const sf::Event::EventType type) const;

   private:
    EventSystem() = default;
    ~EventSystem() = default;
    EventSystem(const EventSystem&) = delete;
    EventSystem& operator=(const EventSystem&) = delete;
    std::unordered_multimap<sf::Event::EventType, sf::Event>
        sfEvents;  ///< Stores events by type
};
}  // namespace MaxrEngine
