import sys

class Partitions:
    def __init__(self):
        self.states = {}
        self.eq_relation = {}
        self.transitions_in_eq_relation = {}
        self.seen_for_epsilon = set()

    def is_epsilon(self, symbol):
        return symbol.startswith('@') and symbol.endswith('@')

    def add_transition(self, from_state, to_state, in_symbol):
        if from_state in self.states:
            self.states[from_state].add((to_state, in_symbol))
        else:
            self.states[from_state] = set([(to_state, in_symbol)])

    def add_state(self, state):
        if state not in self.states:
            self.states[state] = set()

    def recursively_process_epsilons(self, state, partition):
        self.seen_for_epsilon.add(state)
        if partition in self.eq_relation:
            self.eq_relation[partition].add(state)
        else:
            self.eq_relation[partition] = set([state])
        for transition in self.states[state]:
            if self.is_epsilon(transition[1]) and \
                    transition[0] not in self.seen_for_epsilon:
                self.recursively_process_epsilons(transition[0], partition)

    def recursively_process_non_epsilons(self, partition):
        for statenum in self.eq_relation[partition]:
            state = self.states[statenum]
            for transition in state:
                if not self.is_epsilon(transition[1]):
                    self.transitions_in_eq_relation[partition] = \
                        self.transitions_in_eq_relation.get(partition, 0) + 1
                    if transition[0] not in self.seen_for_epsilon:
                        self.recursively_process_epsilons(transition[0],
                                                          partition + 1)

p = Partitions()

for line in sys.stdin.readlines():
    parts = line.split('\t')
    if len(parts) < 4:
        p.add_state(int(parts[0]))
    else:
        from_state, to_state, in_symbol = int(parts[0]), int(parts[1]), parts[2]
        p.add_transition(from_state, to_state, in_symbol)

p.recursively_process_epsilons(0, 0)
equivalence_class_n = len(p.eq_relation)
assert(equivalence_class_n) == 1
while True:
    p.recursively_process_non_epsilons(equivalence_class_n - 1)
    if equivalence_class_n == len(p.eq_relation):
        break
    else:
        equivalence_class_n = len(p.eq_relation)
p.recursively_process_non_epsilons(0)
assert(len(p.eq_relation) == len(p.transitions_in_eq_relation))
for i in range(len(p.eq_relation)):
    print "Class %i has %i transitions, %i states, average %f" % (i, p.transitions_in_eq_relation[i], len(p.eq_relation[i]), float(p.transitions_in_eq_relation[i])/len(p.eq_relation[i]))
