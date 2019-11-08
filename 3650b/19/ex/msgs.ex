defmodule Msgs do
  def printer() do
    receive do
      {:say, msg} -> IO.puts msg
      other -> IO.puts "Huh? #{inspect(other)}"
    end
    printer()
  end

  def startPrinter() do
    Task.start(&printer/0)
  end

  def sender(pid, x) do
    send(pid, {:say, x})
    Process.sleep(1000)
    sender(pid, x + 1)
  end

  def startSender(pid) do
    Task.start(Msgs, :sender, [pid, 0])
  end
end
