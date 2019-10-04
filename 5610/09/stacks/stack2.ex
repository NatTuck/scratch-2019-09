defmodule Stack2 do
  use GenServer

  # Client Interface
  def start_registry do
    Registry.start_link(keys: :unique, name: Stack2.Registry)
  end

  def reg(id) do
    {:via, Registry, {Stack2.Registry, id}}
  end

  def start_link(id) do
    GenServer.start_link(__MODULE__, [173], name: reg(id))
  end

  def push(id, item) do
    # Send a message, no reply or confirmation.
    GenServer.cast(reg(id), {:push, item})
  end

  def pop(id) do
    # Send a message, wait for a reply.
    GenServer.call(reg(id), :pop)
  end

  def print(id) do
    state = GenServer.call(reg(id), :get)
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
