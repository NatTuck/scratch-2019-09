defmodule Demo do
  def fib(x) when x < 2 do
    1
  end

  def fib(x) do
    fib(x - 1) + fib(x - 2)
  end

  def mapFib() do
    {t, v} = :timer.tc(&Enum.map/2, [[38, 38, 38, 38], &fib/1])
    IO.puts "Time: #{t/1000000.0}s"
    v
  end

  def pmap(xs, op) do
    Enum.map(xs, fn x -> Task.async(fn -> op.(x) end) end)
    |> Enum.map(&Task.await/1)
  end

  def pmapFib() do
    {t, v} = :timer.tc(&pmap/2, [[38, 38, 38, 38], &fib/1])
    IO.puts "Time: #{t/1000000.0}s"
    v
  end
end
