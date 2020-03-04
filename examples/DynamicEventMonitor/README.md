# Dynamic Event Monitor

## How to Use
Syntax `$PIN_ROOT/pin -t $PINPP_ROOT/lib/dynamic_event_monitor.dll -l <[layer,layer,...]> -m <method_prefix> -- <executable>`

## Example
- Build `my_shared_lib` and `mock_program` in the `debug` mode;
- Make sure that `my_shared_libd.dll` and `mock_program.exe` are in the same directory;
- Run the executable: `mock_program.exe`;
- Run with tool: `%PIN_ROOT%/pin -t %PINPP_ROOT%/lib/dynamic_event_monitor.dll -- mock_program.exe`;
- Compare the results.

#### Native Execution
```
A greeting is created.    // a Greeting object has two helper methods
Time (long): 100          //   the expected return of Time() method
Content (char *): G       //   the expected return of the Content() method

A hello is created.
Time (int): 200
Content (wchar_t *): 72

A message is created.
Time (long): 300
Content (wchar_t *): 0021DCE0 

A random event is created.
Time (long): 400

Now calling the push methods of different objects

-- Context layer push: Greeting.

-- Servant layer push: Hello.

-- Application layer push: Message.

-- Context layer push: Random_Event.

Time consumption: 62 (ms)
```

#### Execution with Instrumentation
```
Signature found:
Image: f:\git\pinpp\examples\MockProgram\mock_program.exe
Sign: public: void __thiscall Layer_Context::push_greeting(class Greeting *)
Name: Layer_Context::push_greeting
Associated event type: Greeting

Signature found:
Image: f:\git\pinpp\examples\MockProgram\mock_program.exe
Sign: public: void __thiscall Component_Servant::push_hello(class Hello *)
Name: Component_Servant::push_hello
Associated event type: Hello

Signature found:
Image: f:\git\pinpp\examples\MockProgram\mock_program.exe
Sign: public: void __thiscall Component_Context::push_random(class Random_Event *)
Name: Component_Context::push_random
Associated event type: Random_Event

Method call found:
Image: f:\git\pinpp\examples\MockProgram\my_shared_libd.dll
Sign: Layer_Context::push_greeting
Name: Layer_Context::push_greeting

Method call found:
Image: f:\git\pinpp\examples\MockProgram\my_shared_libd.dll
Sign: Component_Servant::push_hello
Name: Component_Servant::push_hello

Method call found:
Image: f:\git\pinpp\examples\MockProgram\my_shared_libd.dll
Sign: Component_Context::push_random
Name: Component_Context::push_random


A greeting is created.
Time (long): 100
Content (char *): G

A hello is created.
Time (int): 200
Content (wchar_t *): 72

A message is created.
Time (long): 300
Content (wchar_t *): 0010DCE0

A random event is created.
Time (long): 400

Now calling the push methods of different objects

..Intercepted a push method call 'Layer_Context::push_greeting' with event type 'Greeting'
  Method: content
Content (char *): G
  Return addr: 1105040
  Method: time
Time (long): 100
  Return addr: 100
-- Context layer push: Greeting.

..Intercepted a push method call 'Component_Servant::push_hello' with event type 'Hello'
  Method: content
Content (wchar_t *): 72
  Return addr: 1105080
  Method: time
Time (int): 200
  Return addr: 200
-- Servant layer push: Hello.

-- Application layer push: Message.

..Intercepted a push method call 'Component_Context::push_random' with event type 'Random_Event'
  Method: time
Time (long): 400
  Return addr: 400
-- Context layer push: Random_Event.

Time consumption: 390 (ms)

Pintool information:
..Target method:
  push

..Target layers:
  Context
  Servant

..Helper methods list:
  Analysis routine for: method 'push_greeting' of component 'Layer' at layer 'Context'
  Analysis routine for: method 'push_hello' of component 'Component' at layer 'Servant'
  Analysis routine for: method 'push_random' of component 'Component' at layer 'Context'

..Mapping between push method and event type:
  Layer_Context::push_greeting <-> Greeting
  Component_Servant::push_hello <-> Hello
  Component_Context::push_random <-> Random_Event

..Helper methods:
  Event: Greeting
    Method: content <-> 1577471072
    Method: time <-> 1577475680
  Event: Hello
    Method: content <-> 1577471232
    Method: time <-> 1577475840
  Event: Random_Event
    Method: time <-> 1577476160
```
#### The Main Differences
- When the executable is loaded, the pin tool will analyze it and locate the signature and actual method addresses of the specified methods, in this case, any method starting with `push` from a class (i.e. layer) of  `context` or `servant`. The associated information will be printed out, which can be turned off if `DEBUG` is set to `0`.
- When the specified method is called, the pin tool will intercept the call, invoke all the registered helper methods of the object passed into the method call, and then execute the original call.
- After the execution is completed, the pin tool will print out its own information, including the specific methods and layers, the mapping between the found methods and their owners and addresses.
