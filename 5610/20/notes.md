
# Web Dev: Testing Your App

## Why test?

 - To make sure it works - tests act kind of like a specification.
 - To make sure it keeps working - avoid regressions.

Testing is really useful for multi-person projects.

 - You add tests to make sure the other programmers don't break your code.

## Testing our apps

Tests are usually written as functions in seperate files from the main
application code.

We have two different major parts of our apps to test:

 - Elixir Code
 - JavaScript code

We also want to be able to test JS and Elixir working together.

Example applications:

 - Inkfish
 - Lens


# Elixir: Kinds of Tests

## Simple Unit Tests

To test pure functions, we just need to call them with some inputs
and make sure we get the right outputs.

## Context Module Unit Tests

Problem: We modify the database.

Ecto's solution:

 - Use an "SQL sandbox"
 - Every test runs inside a transaction, which is rolled back when
   the test completes.

Advantages:

 - Our database doesn't actually change.
 - Transactions are isolated, so we can run multiple tests concurrently.


## Controller Tests

 - Test individual paths in our appilication, going through the full
   chain of elixir code for processing a request.
 - Doesn't test actual network requests.
 - Doesn't test more than one path (controller action function) at once.

## Integration Tests: Simulated

 - Like controller tests, but we can do a sequence of responses.
 - Test programming interface simulates a user using the site.
 - Elixir module: phoenix\_integration

## Integration Tests: With a Real Browser

 - Run a real browser
 - Needs Selenium (or similar)
 - Elixir module: Hound 
 - Alternative elixir module: Wallaby

# Testing JavaScript code

Concrete tools:

 - Jest
 - react-test-rendererer and @testing-library/react

## Simple Unit Tests for Pure Functions

Again, we can test pure functions by calling the function with some
inputs and verifying the expected outputs.

## Testing obnoxious objects with Mock Objects

 - A mock object is an object that looks like (has the same external interface
   as) an object we want to use in tests, but doesn't actually do stuff we don't 
   want (e.g. global state, side effects).

## Testing JS: Summary

 - Write unit tests for small pieces
 - Write larger tests for things like "Pages".
 - Try to test every user action.
 - Use full integration tests (with a browser) to test integration
   with the server.

# Just React

 - create-react-app












 







