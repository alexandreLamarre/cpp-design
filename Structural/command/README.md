### Command

- Ordinary C++ statements are perishable
  - Cannot undo a field/property assignment
  - Cannot directly serialize a sequence of actions (calls)
- Want an object that represents an operation
  - X should change its filed Y to the value Z
  - X should do W()
- Real life usecases : GUI commands, multi-level undo/redo, macro recording


An object which represents an instruction to perform a particular action. Contains all the informaiton n necessary for the action to be taken.

### Command Query Separation
- Command = asking for an action or change (typically mutable, but no return result)
- Query = asking for information (typically immutable, but returns a result)
- CQS = having separate means of sending commands and queries

