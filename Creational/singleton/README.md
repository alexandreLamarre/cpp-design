### Singleton : A component istantiated only once

- Usually a design code smell
- For some components it only makes sense to have on in the system
  - Database repository
  - Object Factory
- Usecase: Constructor call is expensive
  - Want to construct only once
  - We provide everyone with the same instance
- Want to prevent anyone creating additional copies
- Need to take care of lazy instantiation and thread safety

### Summary

- Making a 'safe' singleton is easy
  - Hide or delete the type's constructor, copy constructor and copy assignment operators
  - Create a static method that returns a reference to a static member
  - Guaranteed to be thread-safe since C++11
- Types with 'hard' dependencies on singletons are difficult to test
- Instead of directly using a singleton, consider depending on an asbstraction, i.e. an interface
- Consider defining singleton lifetime in DI container