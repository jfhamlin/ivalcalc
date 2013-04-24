#ifndef __CONSTRAINT_NETWORK_H__
#define __CONSTRAINT_NETWORK_H__

#include "constraint_types.h"
#include "constraint.h"
#include "node.h"

#include <unordered_map>
#include <vector>

namespace allen {

class ConstraintNetwork {
public:

    bool add_node(const Node& n);

    bool is_constraint_consistent(const Constraint& c) const;

    bool add_constraint(const Constraint& c);

private:

    const std::vector<Node> m_nodes;

    typedef std::vector<Constraint> ConstraintVector;

    bool comparable(const Node& n0, const Node& n1) { return true; }

    std::unordered_map<Node::NodeID, ConstraintVector> m_source_node_constraint_map;
};

} // namespace allen

#endif // __CONSTRAINT_NETWORK_H__
