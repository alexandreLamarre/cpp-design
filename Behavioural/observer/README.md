### Observer

- We need to be informed when certain things happen
  - Object's field changes
  - Object does something
  - Some external event occurs
- We want to listen to events and be notified when they occur
- Terminology : 
  - Event and subscriber
  - Signal and slot (Boost,qt, etc...)

Observer : Object that wishes to be informed about events happening in the system. The entity generating the events is an `observer`

### Summary 

Two participants:
  - Observable provides a way of subscribing to an event (signal)
  - Observer performs the subscription

- Observable implementation is always intrusive (observer doesn't need to be)
- Multithreaded/reentrant use can cause issues
- Ready-made implementations of Observer are available