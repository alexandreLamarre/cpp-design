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