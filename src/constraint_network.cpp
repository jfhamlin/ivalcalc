#include "constraint_network.h"
#include <queue>

namespace allen {

bool ConstraintNetwork::add_constraint(const Constraint& c) {
    if (!is_constraint_consistent(c))
        return false;

    std::queue<Constraint> todo;
    todo.push(std::make_pair(c.source().id(), c.dest().id()));

    while (!todo.empty()) {
        Constraint next = todo.front();
        todo.pop();

        const Node& ni = next.source();
        const Node& nj = next.dest();
        const ConstraintTypeSet& added_constraints = next.constraints();

        // Set the relation between the nodes.

        // for each node k such that k, j are comparable:
        for (;;) {
            if (comparable(nk, nk)) {
                ConstraintTypeSet constraints_ki;
                ConstraintTypeSet constraints_kj;

                ConstraintTypeSet new_constraints =
                        lookup_constraint_transitivity(constraints_ki,
                                                       added_constraints);
                new_constraints = constraint_intersection(kj, new_constraints);

                if (new_constraints.is_subset_of(constraints_ki)) {
                    todo.push(Constraint(nk, nj, new_constraints));
                }
            }
        }
    }
}

} // namespace allen
