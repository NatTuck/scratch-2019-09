defmodule Stack1 do
  use GenServer

  # Client Interface

  def start_link(default) do
    GenServer.start_link(__MODULE__, default)
  end

  def push(pid, item) do
    # Send a message, no reply or confirmation.
    GenServer.cast(pid, {:push, item})
  end

  def pop(pid) do
    # Send a message, wait for a reply.
    GenServer.call(pid, :pop)
  end

  def print(pid) do
    state = GenServer.call(pid, :get)
    IO.inspect(state)
  end

  # Implementation
  def init(state0) do
    Process.send_after(self(), :next_odd, 5_000)
    {:ok, state0}
  end

  def handle_call(:pop, _from, [ h | t ]) do
    {:reply, h, t}
  end

  def handle_call(:get, _from, state) do
    {:reply, state, state}
  end

  def handle_cast({:push, item}, state) do
    {:noreply, [item | state]}
  end

  def handle_info(:next_odd, [h | t] = state) do
    Process.send_after(self(), :next_odd, 5_000)
    if rem(h, 2) == 0 do
      {:noreply, state}
    else
      {:noreply, [ h + 2 | t ]}
    end
  end
end
