#ifndef __NODE_H__
#define __NODE_H__

namespace allen {

class Node {
public:

    typedef uint64_t NodeID;

    Node(const NodeID& id): m_id(id) { }

    const NodeID& id() const { return m_id; }

private:

    NodeID m_id;
};

} // namespace allen

#endif // __NODE_H__
