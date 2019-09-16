defmodule Fib do

  # Fibonacci numbers
  #   fib(0) = 0
  #   fib(1) = 1
  #   fib(x) = fib(x-1) + fib(x-2)
  #       where x > 1

  def fib(0), do: 0
  def fib(1), do: 1
  def fib(x) do
    fib(x-1) + fib(x-2)
  end
 
end
