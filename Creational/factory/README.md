### Factory

Initial motivation for a factory design pattern:

- Object creation logic becomes too convoluted
- Constructor is not descriptive
  - Name mandated by name of containing type
  - Cannot overload with same sets of arguments with different names
  - Can turn into 'optional parameter hell'
- Objection creation (non-peicewise, unlike Builder) can be outsourced to
  - A separate function (Factory Method)
  - That mau exist in a separate class (Factory)
  - Can create heirarchy of factories with Abstract Factory


Factory : A component responsible solely for thw wholesale (not piecewise) construction of an Object

### Summary 

- A factory method is a static method that creates objects
- A factory can take care of object creation
- A factory can be external or reside inside the object as an inner class