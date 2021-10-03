### Mediator
- Components may go in and out of a system at any time
  - Chat room participants
  - Players in an MMO
- It makes no sense for them to have direct access to one another
  - those references may go dead
- Solution : have them all refer to some central componient that facilitates communication

Mediator: A component that facilitates communication between other components without them necessarily being aware of each other or having direct (reference) access to each other