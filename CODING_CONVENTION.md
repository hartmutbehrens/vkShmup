#Coding Conventions

This document is mainly here to remind myself of proper guidelines.

## General
- Use pre-increment (prevents unnecessary copies where objects are involved - e.g. iterator)
- Use uniform initialization syntax (brace-initialization) - prevents unintended function definition (aka c++'s [most vexing parse](https://en.wikipedia.org/wiki/Most_vexing_parse)).

## Parameter Passing
- Prefer [simple and conventional](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-conventional) ways of passing parameters
- For “in” parameters, pass cheaply-copied types by value and others by reference to const.
- For “in-out” parameters, pass by reference to non-const
- For “will-move-from” parameters, pass by `X&&` and `std::move` the parameter
- For “forward” parameters, pass by `TP&&` and only `std::forward` the parameter
- For “out” output values, prefer return values to output parameters
- To return multiple “out” values, prefer returning a struct or tuple
- Prefer `T*` over `T&` when “no argument” is a valid option
- Return a `T*` to indicate a position (only! Returning a `T*` to transfer ownership is a misuse.)
- Never (directly or indirectly) return a pointer or a reference to a local object
- Return a `T&` when copy is undesirable and “returning no object” isn’t needed
- Use a lambda when a function won’t do (to capture local variables, or to write a local function)

## Smart Pointer Parameters

- Don’t pass a smart pointer as a function parameter unless you want to use or manipulate the smart pointer itself, such as to share or transfer ownership.
- In other words, prefer passing objects by value, `*`, or `&`, not by smart pointer.
- Express an ownership “sink” function using a by-value unique_ptr parameter (the `unique_ptr` will be moved).
- Use a non-const unique_ptr& parameter only to modify the unique_ptr.
- Don’t use a const `unique_ptr&` as a parameter; use `widget*` instead.
- Express that a function will store and share ownership of a heap object using a by-value `shared_ptr` parameter.
- Use a non-const `shared_ptr&` parameter only to modify the `shared_ptr`.
- Use a `const shared_ptr&` as a parameter only if you’re not sure whether or not you’ll take a copy and share ownership; otherwise use `widget*` instead (or if not nullable, a `widget&`).

See [GotW 91](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/) for further explanation of these guidelines.

## Moving

- To pass a named object `a` as an argument to a && “move” parameter (rvalue reference parameter), write `std::move(a)`. 
- That’s pretty much the only time you should write `std::move`.

## Hierarchy Lifetime
- Use `shared_ptr` to express object lifetime upwards.
```c++
// a <-- b <-- c
// "<--"in the diagram above indicates a shared_ptr
std::shared_ptr<B> b;
b = a->createB();
std::shared_ptr<C> c;
c = b->createC();
```
In the example above `a` must not be deleted before `b` or `c`.

## Allocating Objects

- Where possible, define classes with static (class) factory methods that allocate the object with new and returns a smart pointer.
- This practice prevents raw C pointers from ever escaping to the calling code, and thus avoids the potential for a dangling pointer.
```
	class Widget {
	protected:
	   // Protected constructor
	   Widget();
	   ...
	public:
	   // Static “factory” method
	   static std::shared_ptr<Widget> create();
	};
	
	Widget::Widget() { ... }
	
	std::shared_ptr<Widget> Widget::create() {
	   return std::shared_ptr<Widget>(new Widget());
	}
```