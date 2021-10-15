### Visitor

- Need to define a new operation on an entire class hierarchy
  - E.g. make a document model printable to HTML/Markdown
- Do not want to keep modifying every class in the hierarchy
- Need access to the non-common aspects of classes in the hierarchy
  - Cannot put everything into a single interface
- Create an external component to handle rendering
- Create an external component to handlre rendering
  - But preferably avoid type refects

Visitor: A pattern where a component visitor is allowed to traverse the entire inheritance hierarchy. Implemented by propagating a single `visit()` method throughout the entire hierarchy
