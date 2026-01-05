# Deep Dive: Task 2

Your second task requires that you redefine the inherited behavior of `get_item( )` and `set_item( )`. To begin with, let's look at their function signatures:

```c++
/**
 * @brief Update the item in this lock box.
 * @details We can only set a new item in the lock box if it is not currently locked or locked out.
 * @pre the box is not locked or locked out.
 * @post the box contains the given item.
 */
void set_item( const T &item ) override;

/**
 * @brief Access a copy of the item in this lock box.
 * @details We can only access the item in this lock box if it is not currently locked or locked out.
 * @pre the box is not locked or locked out.
 * @post a copy of the item in this lock box is returned.
 * @throw std::logic error if invoked when this box is locked or locked out.
 */
auto get_item( ) const -> T override;
```

## Throwing Exceptions

You'll notice that with `get_item( )`, we specify that we should throw an exception when we try to access the item in a locked (or locked out) box. Why is that? When we look at the method signature, we see that it specifies a return value -- the item in the box. However, in the case the box is locked, or locked out, we have nothing to return. The method signature indicates we _have_ to return a value; conditions indicate we can't. Thus, we exist in an "exceptional" state and must instead, throw an exception as we have nothing really, to return.

We'll learn more about exceptions later in the semester, but for now, we just need to know how to throw an exception. Specifically, as the Doxygen comments suggest with the `@throw` tag, we must throw a `std::logic_error` exception. First, however, we must have access to this class of exception. This is done by including the `stdexcept` library.

```c++
#include <stdexcept>

namespace csc232 
{
    // ...
    template<typename T>
    auto LockBox::get_item( ) const -> T 
    {
        // ... determine appropriate condition
        if (appropriate_condition) 
        {
            throw std::logic_error( "Attempting to retrieve an item from a locked box" );   
        }
        // no need for else since we get here if the box wasn't locked or locked out
        return plain_box< T >::get_item( );
    }
    // ...
}
```

We can use the same message (the string argument passed to the `logic_error` constructor) for whether the box is currently locked, or locked out. The message is valid, i.e., semantically correct, under either condition. Notice too, if conditions are satisfied, we delegate to our parent class (`plain_box<T>`) the behavior of returning the item in the box.

## Writing to Standard Error Output Stream

So why not throw an exception with the `set_item( )` method? While we face similar conditions, this mutator method does not return a value, so we don't have to worry about trying to perform an impossible task. Instead, we can just log an error message to the standard error output stream, `std::cerr`. Writing to `std::cerr` is no different from writing to `std::cout` as they are both output streams.

```c++
namespace csc232 
{
    // ...
    template<typename T>
    auto LockBox::set_item( const T& item) -> void
    {
        // ... determine appropriate condition
        if (appropriate_condition) 
        {
              plain_box< T >::set_item( item );
        }
        else 
        {
            std::cerr << "Attempt to add item to locked box." << std::endl;
        }
    }
    // ...
}
```
