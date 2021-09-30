### Proxy

- You are calling foo.bar()
- his assumes that foo is in the same process as bar()
- What if, later on, you want to put all Foo-related operations in a separate process?
  - Can you avoid changing your code?
- Proxy to the rescue!
  - Same interface, entirely different behaviour
- This is called a "communication proxy"
  - Other types : logging, virtual, guarding,...

A class that functions as an interface to a particular resource. That resource may be remote, expensive to construct or may require logging or some other added functionality
