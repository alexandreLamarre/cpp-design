### Prototype
- Complicated objects (e.g., cars) aren't designed from scratch
  - They reiterate existing designs
- An existing (partially or fully constructed) design is a Prototype
- We make a copy (close) the prototype and customize it
  - Requires 'deep copy' support

Prototype : A partially or fully initialized object that you copy (clone) and make use of

### Summary 

- To implement a prototype, partially construct an object and store it somewhere

- Clone the prototype:
  - Implement your own deep copy functionality
  - Serialize and deserialize
- Customize the resulting instance