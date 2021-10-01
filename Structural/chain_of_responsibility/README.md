### Chain of Responsibilty

Example:
- Click a Graphical element on a form
  - Button handles it, stops further processing
  - Underlying group box
  - Underlying window

A chain of components who all get a chance to process a command or a query, optionally having default processing implementation and an ability to terminate the processing chain

### Summary

- CoR can be implemented as 
  - A chain of pointer/references (singly linked list)
  - Centralized list
- Enlist objects in the chain, possibly controlling their order
- Object removal from chain (e.g. disconnect from a signal)