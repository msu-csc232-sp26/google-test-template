# Deep Dive: Task 1

This document provides a deeper dive into the steps needed to complete the first task.

## Getting Started

The first step asks that you create a new file in a particular location in the file system. The name and location of this new (header) file is crucial. If you do not name it correctly, or place it in the expected directory, your test target will not compile.

The basic structure of the header file should be as follows:

```c++
/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    Filename.h
 * @author  Youe Name <your email address>
 * @brief   A brief description of the contents, or purpose of this file.
 * @version 1.0.0
 * @date    MM/DD/YY
 */

#ifndef SOME_UNIQUE_NAME
#define SOME_UNIQUE_NAME

/**
 * @brief Namespace used to encapsulate coursework.
 */
namespace someNamespace 
{
    /**
     * @brief A brief descripton of this class.
     * @tparam SomeType A brief description of the type parameter.
     */
    template< typename SomeType >
    class ChildClass : public ParentClass< T > 
    {
    public:
        /**
         * @brief Default constructor
         * @note This is what we refer to as Doxygen-style comments.
         *       See Appendix C - C++ Documentation Systems
         */
        ChildClass( );
        
        // the rest of the public interface
    private:
        // Data member declarations/initializations
        // We generally do not use Doxygen-style comments on private
        // data members or private member functions.
        int some_uninitialized_data_member_; // this should be initialized in an
                                             // initialization list when this class
                                             // is defined in the corresponding 
                                             // source file (.cpp)
        bool some_initialized_data_member_ = false; // no need to initialize in 
                                                    // initializer list
    };
}
#endif // SOME_UNIQUE_NAME
```

Notice there is a lot of documentation. Your assignments have a "style" grading component to them and these comments (or lack thereof) affect that grade. Also note, these Doxygen-style comments appear only in the header (specification) files; use single-line or multi-line style comments in your source (*.cpp) files when you find the need to document your code.

### Typical tags in Doxygen comments

Depending on the context, a number of tags should appear in your comments:

| Tag       | Purpose                                                                          |
|-----------|----------------------------------------------------------------------------------|
| `@author` | Lists the name of the module's programmer.                                       |
| `@brief`  | Used to provide a brief description.                                             |
| `@date`   | Used to provide a timestamp for the module.                                      |
| `@file`   | Identifies the name of the file containing a class.                              |
| `@param`  | Identifies a function's parameter by name and includes a description.            |
| `@post`   | Identifies a function's post condition(s).                                       |
| `@pre`    | Identifies a functions's pre condition(s).                                       |
| `@return` | Describes a function's return value.                                             |
| `@throw`  | Lists an exception that a function can throw.                                    |
| `@tparam` | Identifies a template class template parameter that also includes a description. |

#### Tips on commenting

* Use `/** */` (i.e., Doxygen-style) comments before headers of files, namespaces, classes, and functions to document their use and specification. Use tags within a comment to identify aspects of the documentation.
* Use `//` (i.e., single-line) comments within the body of a class declaration or function definition that describes the details of the implementation.
* Use `/* */` (i.e., multi-line) comments during debugging to temporarily disable a portion of your code.

Again, see [Appendix C](https://msu.vitalsource.com/reader/books/9780138122782/epubcfi/6/608%5B%3Bvnd.vst.idref%3DP70010183410000000000000000076A5%5D!/4/2%5BP70010183410000000000000000076A5%5D/2/2%5BP70010183410000000000000000076A6%5D/7:8%5Bocu%2Cmen%5D) for more details.

## File names and locations

In this first task, you're asked to create two files in two different locations in the file system:

1. `lock_box.h` - a header file, also known as a specification file. This belongs in the `include` directory of your project.
2. `lock_box.cpp` - the corresponding source file. This belongs in the `src/main/cpp` directory of your project.

That is, when this task is completed, your file system will appear as (with some files and directories removed for brevity/clarity):

```shell
.
├── CMakeLists.txt
├── include
│   ├── box.h
│   ├── csc232.h
│   ├── lock_box.h
│   ├── magic_box.h
│   ├── plain_box.h
│   └── toy_box.h
├── src
│   ├── main
│   │   ├── cpp
│   │   │   ├── demo.cpp
│   │   │   ├── expanded_templates.cpp
│   │   │   ├── lock_box.cpp
│   │   │   ├── magic_box.cpp
│   │   │   ├── main.cpp
│   │   │   ├── plain_box.cpp
│   │   │   └── toy_box.cpp
│   │   └── resources
│   │       ├── class-diagram.puml
│   │       ├── demo_data.txt
│   │       └── main_data.txt
│   └── test
│       ├── cpp
│       │   ├── base_test_fixture.h
│       │   ├── testing.md
│       │   └── unit_tests.cpp
│       └── resources
│           ├── task1_test_data.txt
│           ├── task2_test_data.txt
│           ├── task3_test_data.txt
│           ├── task4_test_data.txt
│           ├── task5_test_data.txt
│           └── test_data.txt
├── task1.md
├── task2.md
└── task3.md
```

Your source file will need to include the header file, specified as:

```c++
#include "lock_box.h"
```

Given the header file and corresponding source file are not in the same directory, you would think that this wouldn't compile. The `#include` directive does not provide the correct relative location of the header file with respect to the source file's location. Normally, this would be an issue, as shown below.

```shell
clang++ -c lock_box.cpp 
lock_box.cpp:14:10: fatal error: 'lock_box.h' file not found
   14 | #include "lock_box.h"
      |          ^~~~~~~~~~~
1 error generated.                                                                                           
```

Note: We use a compiler option (`-c`) to compile only (to produce an object file) without attempting to link it with other files to produce an executable.

However, if you were to compile this file in the same manner, albeit by specifying a location of the include files, we do not get this error:

```shell
clang++ -c lock_box.cpp -I ../../../include
```

Here, we also use the `-I` compiler option to specify (in a relative manner) the location of any local include files (i.e., header files that aren't part of the system include files).

All our projects are "cmake" projects, meaning, we use a tool named `cmake` to help with the tasks related to compiling, linking, and other software development activities. A file named `CMakeLists.txt` provides instructions to our C++ compiler on where to locate any include files that are part of the system include files. Thus, if your IDE isn't configured to recognize the `cmake` nature of our project, it may complain that it can't file the header file. Thus, it would behoove you to make sure your IDE is using something to help in this regard. Visual Studio Code, Visual Studio, Clion and many other modern IDEs have support for cmake projects, either directly, or via some plugin or extension.

For example, Clion (by JetBrains) has built-in support for cmake-based projects. When Clion loads such a project, it reads the `CMakeLists.txt` file and uses it to set up the executable targets (or simply, targets) that are easily built and executed with the click of a button. CLion's targets are show below for this project:

![Clion cmake targets](img/clion-cmake-targets.png)

Likewise, here is the equivalent in Visual Studio Code's CMake extension:

![Visual Studio Code cmake targets](img/vscode-cmake-targets.png)

Thus, when instructed to build and/or execute the `unit_tests` target, this is simply a matter of clicking a button on these tools. In Clion, the "hammer" icon is on the button to build a target (i.e., compile and link into an executable), and the "play" button is used to "run" or "execute" a given target, and a little "bug" icon is used to launch a debugger to debug your program.

![Clion development tools](img/clion-buttons.png)

## More notes on style

When you push your code to GitHub, an automated workflow (GitHub action) runs that not only attempts to compile, build, and execute the `unit_tests` target, but it also runs a "linter" to check both your programming style and adherence to modern programming idioms. On that last point (modern programming idioms), you'll most likely find that you're forced to write your source code in a particular manner. One of the most common "issues" students face comes to the notion of a "trailing return type." Consider the following function declaration:

```c++
bool foo( int bar );
```

Seems simple enough, but this won't make it by the linter. The linter will complain and suggest you use trailing return types. To fix this issue, rewrite the code as:

```c++
auto fool( int bar ) -> bool;
```

Here, we're using the keyword `auto` to tell the compiler to infer the return type, and we use the trailing return type (`-> bool`) to help with that inference.

Another common "issue" is declaring variables whose names are too short; the linter will want identifiers to be at least 3 characters long. For example, the linter will complain about:

```c++
int x;
```

This can be fixed by making the identifier at least three characters long:

```c++
int x_coord; // or x_coordinate
```

This encourages programmers to write semantically-rich code: `x_coord` means a lot more to me in my mind than just `x`.

The README provides you with a command that can make sure you're on the right track _before_ you push your code to GitHub. If your IDE isn't configured to use `clang-format` or `clang-tidy` to do this automatically for you, you can always do this on your own by typing the following command on command line (from the root directory of your project):

```shell
find ./include ./src -name '*.h' -o -name '*.hpp' -o -name '*.c' -o -name '*.cpp' | xargs clang-format -i
```

This command looks for any file that has the `.h`, `.hpp`, `.c` or `.cpp` extension in the `include` and `src` folders (and subfolders) and "pumps" them into another program (`clang-format`) to automatically "fix" them, if possible.

You can also see the results of the unit tests and the linter in GitHub

![GitHub actions](img/linter-report.png)

If there are problems, the Cpp-Linter Report will identify them for you. The `run-autograding-tests` job runs `ctest` which executes the test target. As you might expect, both of these jobs should be "green," i.e., passing, in order to maximize your chances for a perfect grade. Note: Even if these both pass, it is not a guarantee that you'll get a perfect grade. For example, if you were asked to code some task using recursion, but instead your solution uses an iterative control structure, you won't get a perfect sore. Even though the tests may pass, you didn't follow directions.

## Implementation Details

### Constructor

The `lock_box` constructor takes a single parameter of type `std::string`. As such, your `lock_box.cpp` (where the implementation details are found) needs to `#include <string>`. Also, specifications indicate that the password cannot be empty. Thus, in the body of the constructor, you should check that the given parameter is not empty. If it is, you should throw an exception. We'll learn more about exceptions soon, but for now, know that in this case, you're expected to throw a particular kind of exception: `invalid_argument`.

Firstly, to throw this exception, you'll need to `#include<stdexcept>`. Then, where needed (in this case, the constructor), you throw an exception as follows:

```c++
throw std::invalid_argument( "password must be non-empty" );
```

Also, to prevent an implicit type conversion between a string and lock_box, you should mark this constructor as `explicit` (in the constructor declaration in the `lock_box.h` header file):

```c++
explicit lock_box( std::string password );
```

### Destructor

Your destructor can simply utilize the default implementation provided by the C++ language. This can be realized by either writing an empty body, or assigning it `default`. That is,

```c++
template < class T >
lock_box< T >::~lock_box( ) = default;
```

is equivalent to

```c++
template < class T >
lock_box< T >::~lock_box( )
{
    // intentionally empty
}
```

## Overriding Existing Behavior

The `lock_box<T>` class template inherits, and ultimately, will redefine, the `get_item( )` and `set_item( )` methods. Before we get into the specifics of the redefined behavior (reserved for Task 2), we will simply delegate to the parent class:

```c++
template < typename T >
auto lock_box< T >::get_item( ) const -> T
{
    return plain_box< T >::get_item( );
}
```

Similarly, for the `set_item( )` method.

## Extending Behavior

We extend the `plain_box<T>` class with new accessor methods as well as additional methods that model the locking behavior of the lock box.

### Accessor methods

The accessor methods (`is_locked( )` and `is_lockedOut( )`) should simply return the values of the data members for which they are providing access. For example,

```c++
template < class T >
auto lock_box< T >::is_locked( ) const -> bool
{
    return locked_;
}
```

Similarly, for `is_lockedOut`.

### Additional behavior

For this first task, we will simply stub out one of these methods until we refine it in task 3. As a stub, `unlock( )` should just return `false`. The other method, `lock( )`, should set the value of the `locked_` data member to `true`.

## Namespaces

Our design specifies that the classes we develop are part of the `csc232` namespace. Our design also indicates that the `lock_box` is a subclass (child) of `plain_box`. That means, in the header (specification) file, we have

```c++
namespace csc232
{
    template < class T >
    class lock_box : public plain_box< T >
    {
    public:
        // ...
        auto is_locked( ) const -> bool;
        // ... 
    private:
        // data member declarations
    };

} // csc232
```

When it comes to implementing these methods in the source file, you need to indicate that these member functions are members of class that is a member of a namespace. This can be done in one of two ways:

```c++
namespace csc232 
{
    template < class T >
    auto lock_box< T >::is_locked( ) const -> bool
    {
        return locked_;
    }
}
```

or

```c++
template < class T >
auto csc232::lock_box< T >::is_locked( ) const -> bool
{
    return locked_;
}
```

The scope resolution operator (`::`) is telling us that `is_locked( )` is scoped to, or a member of, the `lock_box< T >` class template, and that the `lock_box< T >` class template is scoped to, or a member of, the `csc232` namespace.

For more information on namespaces and the scope resolution operator, see [Appendix A.11 Namespaces](https://msu.vitalsource.com/reader/books/9780138122782/epubcfi/6/596%5B%3Bvnd.vst.idref%3DP7001018341000000000000000007475%5D!/4/2%5BP7001018341000000000000000007475%5D/2/2%5BP7001018341000000000000000007476%5D/3:8%5Bpac%2Ces%5D).
