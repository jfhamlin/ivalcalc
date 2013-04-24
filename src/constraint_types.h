#ifndef __CONSTRAINT_TYPES_H__
#define __CONSTRAINT_TYPES_H__

#include <cstdint>

namespace allen {

enum CONSTRAINT_TYPE {
    CONSTRAINT_TYPE_EQUAL,         // =
    CONSTRAINT_TYPE_BEFORE,        // <
    CONSTRAINT_TYPE_AFTER,         // >
    CONSTRAINT_TYPE_DURING,        // d
    CONSTRAINT_TYPE_CONTAINS,      // di
    CONSTRAINT_TYPE_OVERLAPS,      // o
    CONSTRAINT_TYPE_OVERLAPPED_BY, // oi
    CONSTRAINT_TYPE_MEETS,         // m
    CONSTRAINT_TYPE_MET_BY,        // mi
    CONSTRAINT_TYPE_STARTS,        // s
    CONSTRAINT_TYPE_STARTED_BY,    // si
    CONSTRAINT_TYPE_FINISHES,      // f
    CONSTRAINT_TYPE_FINISHED_BY,   // fi
    CONSTRAINT_TYPE_COUNT
};

inline CONSTRAINT_TYPE inverse(CONSTRAINT_TYPE type) {
    if (type == CONSTRAINT_TYPE_EQUAL)
        return type;
    // -1 for even types, +1 for odd types.
    return type - 1 + ((type & 0x1) << 1);
}

#define CONSTRAINT_TYPE_BIT(type) (0x1 << (type))

class ConstraintTypeSet {
public:

    ConstraintTypeSet(): m_constraint_bits(0) { }
    ConstraintTypeSet(CONSTRAINT_TYPE type): m_constraint_bits(0) { add(type); }

    bool is_valid() const { return (m_constraint_bits != 0); }

    bool contains(CONSTRAINT_TYPE type) const {
        return m_constraint_bits & CONSTRAINT_TYPE_BIT(type);
    }

    void add(CONSTRAINT_TYPE type) {
        m_constraint_bits |= CONSTRAINT_TYPE_BIT(type);
    }

    void remove(CONSTRAINT_TYPE type) {
        m_constraint_bits &= ~CONSTRAINT_TYPE_BIT(type);
    }

private:

    ConstraintTypeSet(uint32_t bits): m_constraint_bits(bits) { }

    friend ConstraintTypeSet constraint_union(const ConstraintTypeSet&,
                                              const ConstraintTypeSet&);
    friend ConstraintTypeSet constraint_intersection(const ConstraintTypeSet&,
                                                     const ConstraintTypeSet&);
    friend ConstraintTypeSet lookup_constraint_transitivity(
            const ConstraintTypeSet&, const ConstraintTypeSet&);

    uint16_t m_constraint_bits;
};

inline ConstraintTypeSet constraint_union(const ConstraintTypeSet& c0,
                                          const ConstraintTypeSet& c1) {
    return ConstraintTypeSet(c0.m_constraint_bits | c1.m_constraint_bits);
}

inline ConstraintTypeSet constraint_intersection(const ConstraintTypeSet& c0,
                                                 const ConstraintTypeSet& c1) {
    return ConstraintTypeSet(c0.m_constraint_bits & c1.m_constraint_bits);
}

ConstraintTypeSet lookup_constraint_transitivity(const ConstraintTypeSet& c0,
                                                 const ConstraintTypeSet& c1);

} // namespace allen

#endif // __CONSTRAINT_TYPES_H__
