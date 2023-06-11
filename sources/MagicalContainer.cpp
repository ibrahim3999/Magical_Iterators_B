
#include "MagicalContainer.hpp"

using namespace ariel;
// Default constructor
MagicalContainer::MagicalContainer() : vecElements(), vecPrime() {}

void MagicalContainer::addElement(int element) {
    if (isPrime(element)) {
        auto it = lower_bound(vecPrime.begin(), vecPrime.end(), element);
        if (it == vecPrime.end() || *it != element) {
            vecPrime.insert(it, element);
        }
    }
    auto it = lower_bound(vecElements.begin(), vecElements.end(), element);
    if (it == vecElements.end() || *it != element) {
        vecElements.insert(it, element);
    }
}

void MagicalContainer::removeElement(int element) {
    if (isPrime(element)) {
        auto it = lower_bound(vecPrime.begin(), vecPrime.end(), element);
        if (it != vecPrime.end() && *it == element) {
            vecPrime.erase(it);
        }
    }

    auto it = std::lower_bound(vecElements.begin(), vecElements.end(), element);
    if (it != vecElements.end() && *it == element) {
        vecElements.erase(it);
        return;
    }
    throw std::runtime_error("No element!!!");
}

size_t MagicalContainer::size() const {
    return vecElements.size();
}

bool MagicalContainer::isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    else if (number <= 3) {
        return true;
    }
    else if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }

    int i = 5;
    while (i * i <= number) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
        i += 6;
    }
    return true;
}

const std::vector<int>& MagicalContainer::getElements() const {
    return vecElements;
}

// iterator class for iterating over the elements of the MagicalContainer in ascending order. It inherits from a base Iterator class.
MagicalContainer::AscendingIterator::AscendingIterator() : Iterator(IteratorType::ASCENDING), index(0),container(*new MagicalContainer()) {

}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : Iterator(IteratorType::ASCENDING),index(0), container(container) {

}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index) : Iterator(IteratorType::ASCENDING),index(index),container(container) {
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : Iterator(IteratorType::ASCENDING), index(other.index), container(other.container) {

}

MagicalContainer::AscendingIterator::~AscendingIterator() = default;


MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
    if (*this != other) {
        if (&container != &other.container) {
            throw runtime_error("Error with operator=() :: AscendingIterator!!!");
        }
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator==():: AscendingIterator!!!.");
    }
    return index == other.index;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator>()::: AscendingIterator!!!.");
    }
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {

    return !(*this > other || *this == other);
}

int MagicalContainer::AscendingIterator::operator*() const {
    if (index < 0 || index >= container.size()) {
        throw runtime_error("Iterator out of bound operator*()");
    }
    return container.vecElements[index];
}
//overload moves the iterator to the next element.
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    if (++index > container.size()) {
        throw runtime_error("Error with operator++() out bound");
    }
    return *this;
}
// static method returns an iterator pointing to the first element of the 
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return AscendingIterator(container, 0);
}
//method returns an iterator pointing to the position past the last element of the MagicalContainer
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    return AscendingIterator(container, container.size());
}

MagicalContainer &MagicalContainer::AscendingIterator::getContainer() const {
    return container;
}

size_t MagicalContainer::AscendingIterator::getIndex() const {
    return index;
}

bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator==()AscendingIterator ");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this == otherAscendingIterator;
}

bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator!=() AscendingIterator");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this != otherAscendingIterator;
}

bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator>() AscendingIterator");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this > otherAscendingIterator;
}

bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator<() AscendingIterator");
    }
    const auto &otherAscendingIterator = dynamic_cast<const AscendingIterator &>(other);
    return *this < otherAscendingIterator;
}
MagicalContainer::SideCrossIterator::SideCrossIterator() : Iterator(IteratorType::SIDE_CROSS), frontIndex(0),backIndex(container.size() - 1),container(*new MagicalContainer()) {

}
//This is an iterator class for iterating over the elements of the MagicalContainer in a side-to-center and center-to-side fashion. It also inherits from the Iterator base class.
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : Iterator(
        IteratorType::SIDE_CROSS), frontIndex(0), backIndex(container.size() - 1), container(container) {
    if (container.size() == 0) {
        backIndex = 0;
    }
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t frontIndex, size_t backIndex): Iterator(IteratorType::SIDE_CROSS), frontIndex(frontIndex), backIndex(backIndex), container(container) {
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) : Iterator(IteratorType::SIDE_CROSS), frontIndex(other.frontIndex), backIndex(other.backIndex),container(other.container) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() = default;

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
    if (*this != other) {
        if (&container != &other.container) {
            throw runtime_error("Error with operator=()::SideCrossIterator:");
        }
        frontIndex = other.frontIndex;
        backIndex = other.backIndex;
    }
    return *this;
}
// operators MagicalContainer::SideCrossIterator
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator==()::SideCrossIterator:");
    }
    return (frontIndex == other.frontIndex && backIndex == other.backIndex);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator>()::SideCrossIterator:");
    }
    // The iterator closer to the middle is considered "greater"
    return (min(frontIndex, backIndex) > min(other.frontIndex, other.backIndex));
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator<()::SideCrossIterator:");
    }
    // The iterator closer to the start/end is considered "lesser"
    return (max(frontIndex, backIndex) < max(other.frontIndex, other.backIndex));
}


MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
    if (frontIndex > backIndex) {
        throw runtime_error("Error with operator++(): Iterator has reached its end.");
    }
    // If we are at an even count of increments, we increment the front index.
    // Otherwise, we decrement the back index.
    if (increments % 2 == 0) {
        frontIndex++;
    } else {
        backIndex--;
    }
    increments++;
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const {
    if (frontIndex > backIndex) {
        throw runtime_error("Error with operator*(): out bound");
    }
    // If we are at an even count of increments, we return from the front.
    // Otherwise, we return from the back.
    if (increments % 2 == 0) {
        return container.vecElements[frontIndex];
    } else {
        return container.vecElements[backIndex];
    }
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    return {container, 0, container.size() - 1};
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    size_t mid = (container.size() + 1) / 2;
    if (mid == 0) {
        return {container, mid, mid};
    }
    return {container, mid, mid - 1};
}


MagicalContainer &MagicalContainer::SideCrossIterator::getContainer() const {
    return container;
}

size_t MagicalContainer::SideCrossIterator::getFrontIndex() const {
    return frontIndex;
}

size_t MagicalContainer::SideCrossIterator::getBackIndex() const {
    return backIndex;
}

bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator==()::SideCrossIterator");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this == otherSideCrossIterator;
}

bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator!=()::SideCrossIterator");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this != otherSideCrossIterator;
}

bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator>()::SideCrossIterator");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this > otherSideCrossIterator;
}

bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator<()::SideCrossIterator");
    }
    const auto &otherSideCrossIterator = dynamic_cast<const SideCrossIterator &>(other);
    return *this < otherSideCrossIterator;
}
MagicalContainer::PrimeIterator::PrimeIterator() : Iterator(IteratorType::PRIME) ,index(0), container(*new MagicalContainer()) {}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : Iterator(IteratorType::PRIME), index(0), container(container) {
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index) : Iterator(IteratorType::PRIME), index(index),container(container) {

}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) : Iterator(IteratorType::PRIME), index(other.index),container(other.container) {

}

MagicalContainer::PrimeIterator::~PrimeIterator() = default;

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
    if (*this != other) {
        if (&container != &other.container) {
            throw runtime_error("Error with operator=()::PrimeIterator");
        }
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator==()::PrimeIterator");
    }
    return index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
    if (&container != &other.container) {
        throw runtime_error("Error with operator>()::PrimeIterator");
    }
    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {

    return !(*this > other || *this == other);
}

int MagicalContainer::PrimeIterator::operator*() const {
    if (index < 0 || index >= container.vecPrime.size()) {
        throw runtime_error("Error with operator*()::PrimeIterator");
    }
    return container.vecPrime[index];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
    if (++index > container.vecPrime.size()) {
        throw runtime_error("Error with operator++()::PrimeIterator");
    }
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    return PrimeIterator(container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    return PrimeIterator(container, container.vecPrime.size());
}

MagicalContainer &MagicalContainer::PrimeIterator::getContainer() const {
    return container;
}

size_t MagicalContainer::PrimeIterator::getIndex() const {
    return index;
}


bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator==()::PrimeIterator");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this == otherPrimeIterator;
}

bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator!=()::PrimeIterator");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this != otherPrimeIterator;
}

bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator>()::PrimeIterator");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this > otherPrimeIterator;
}

bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::Iterator &other) const {
    if (this->getIterType() != other.getIterType()) {
        throw runtime_error("Error with operator<()::PrimeIterator");
    }
    const auto &otherPrimeIterator = dynamic_cast<const PrimeIterator &>(other);
    return *this < otherPrimeIterator;
}






