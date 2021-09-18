## SOLID principles

### Single Responsibilty Principle
- A class should only have one reason to change
- *Separation of concerns* - different classes handling different, independent tasks/problems

### Open-Closed Principle
- Classes should be open for extension but closed for modification

### Liskov Substitution Principle
- You should be able to substitute a base type for a subtype

### Interface Segregation Principle
- Don't put too much into an interface; split into separate interfaces
- YAGNI: You ain't gonna need it

### Dependency Inversion Principle
- High-level modules should not depend upon low-level ones; use abstractions



#### Note : Gamma Categorization
- Design patterns are typically split into three categories

- Creational Patterns
  - Deal with the creation (construction) of objects
  - Explicit (constructor) vs. implicit (DI, reflection, etc...)
  - Wholesale (single statement) vs. piece-wise (step-by-step)
- Structural Patterns
  - Concerned with the structure (class members)
  - Many patterns are wrappers that mimic the underlying class interface
  - Stress the importance of good API design
- Behavioral Patterns
  - They are all different; no central theme