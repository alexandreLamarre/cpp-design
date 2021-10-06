### Memento
- An object or system that goes through changes
- E.g. a bank account gets deposits and withdrawals
- There are different ways of navigating those changes
- One way is to record every change (Command) and teach a command to 'undo' itself
- Another is to simply save a snapshot of the system.

Memento : A token/handle representing the system state. Lets us roll back to the state when the token was generated. May or not directly expose state information

### Summary

- Mementos are used to rol back states arbitrarily
- A memento is simply a token/handle class with typically no functions of its own
- A meneto is not required to expose directly the state to which it reverts the system
- Can be used to implement undo/redo