### Composite

- Objects use other object's fields, properties, members through inheritance and composition
- Composition lets us make compound objects
  - A mathematical expression composed of simple expressions
  - A grouping of shapes that consist of several shapes
- Composite design pattern is used to treat both single (scalar) and composite objects uniformly
  - e.g. Foo and Collection<Foo> has similar APIs

A mechanism for treating individual (scalar) objects and compositions of objects in uniform manner

### Summary 

- Objects can use other objects via inheritance/composition
- Some composed and singular objects need similar/identical behaviours
- Composite design patterns lets us treat both types of objects uniformly
- C++ uses duck typing, expecting enumerable types to provide begin()/end()
- A single object cn masquerade as a collection