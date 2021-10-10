### State

- Consider an ordinary telephone
- What to do with it depends on the state of the phone/line
  - If ringing or you want to make a call, you can pick it up
  - Phone must be off the hook to talk/ make a call
  - If you try calling someone and its busy, you put the handset down
- Changes in state can be explicit or in reponse to event (Observer)

State : A pattern in which the object's behaviour is determined by its state. An object tranistions from on state to another (something needs to trigger a transition).

A formalized construct which manages state and transitions is called a state machine.

### Summary 
- Given sufficient complexity, it pays to formally define possible states and events/triggers
- Can define:
  - State entry and exit behaviours
  - Action when a particular event causes a transition
  - Guard conditions when enabling and disabling a transition
  - Default action when no transitions are found for an event