defmodule RW do
  def loop() do
    case IO.gets("input: ") do
      :eof ->
        IO.puts "All done"
      {:error, reason} ->
        IO.puts "Error: #{reason}"
      line ->
        IO.puts(reverse_words(line))
        loop()
    end
  end

  def reverse_words(line) do
    String.split(line)
    |> Enum.reverse()
    |> Enum.join(" ")
  end
end

RW.loop()

