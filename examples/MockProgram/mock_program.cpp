// mock_program.cpp

// release mode uses my_shared_lib.lib
// debug mode uses my_shared_libd.lib

#include <iostream>
#include <string>
#include <ctime>
#include "my_shared_lib.h"

int main (int argc, char * argv [])
{
  std::clock_t start = std::clock ();

  bool run_fibonacci = false;

  int total_loop = 10000;
  if (argc == 2)
  {
    run_fibonacci = true;
    std::cout << "Loop count: " << atoi(argv[1]) << std::endl;
    total_loop = atoi(argv[1]);
  }
  
  if (run_fibonacci)
  {
    for (int i = 0; i < total_loop; ++i)
    {
      fn_fibonacci (100, false);
    }
  }
  else
  {
    std::cout << std::endl;

    char * content_greeting = "Greeting!";
    Greeting * greeting = new Greeting (100, content_greeting);
    std::cout << "A greeting is created." << std::endl;
    greeting->time ();
    greeting->content ();
    std::cout << std::endl;

    wchar_t * content_hello = L"Hello~";
    Hello * hello = new Hello (200, content_hello);
    std::cout << "A hello is created." << std::endl;
    hello->time ();
    hello->content ();
    std::cout << std::endl;

    wchar_t * content_message = L"This is a message.";
    Message * message = new Message (300, content_message);
    std::cout << "A message is created." << std::endl;
    message->time ();
    message->content ();
    std::cout << std::endl;

    Random_Event * random_event = new Random_Event (400);
    std::cout << "A random event is created." << std::endl;
    random_event->time ();
    std::cout << std::endl;
    
    Layer_Context layer_context;
    Component_Servant component_servant;
    Laboratory_Application laboratory_application;
    Component_Context component_context;
    
    std::cout << "Now calling the push methods of different objects" << std::endl << std::endl;

    layer_context.push_greeting (greeting);
    std::cout << std::endl;
    
    component_servant.push_hello (hello);
    std::cout << std::endl;
    
    laboratory_application.push_message (message);
    std::cout << std::endl;
    
    component_context.push_random (random_event);
    std::cout << std::endl;

    if (greeting != 0)
    {
      delete greeting;
      greeting = 0;
    }

    if (hello != 0)
    {
      delete hello;
      hello = 0;
    }

    if (message != 0)
    {
      delete message;
      message = 0;
    }

    if (random_event != 0)
    {
      delete random_event;
      random_event = 0;
    }
  }

  std::clock_t end = std::clock ();
  std::cout << "Time consumption: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " (ms)" << std::endl;

  return 0;
}
