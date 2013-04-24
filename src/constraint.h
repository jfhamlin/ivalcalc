#ifndef __ALLEN_CONSTRAINT_H__
#define __ALLEN_CONSTRAINT_H__

#include "constraint_types.h"

namespace allen {

class Node;

class Constraint {
public:
    Constraint(const Node& source, const Node& dest, const ConstraintTypeSet& cts)
        : m_source(source), m_dest(dest), m_constraints(cts) { }

    const Node& source() const { return m_source; }
    const Node& dest() const   { return m_dest; }

    const ConstraintTypeSet& constraints() const { return m_constraints; }

private:
    const Node& m_source;
    const Node& m_dest;

    ConstraintTypeSet m_constraints;
};

} // namespace allen

#endif // __ALLEN_CONSTRAINT_H__
