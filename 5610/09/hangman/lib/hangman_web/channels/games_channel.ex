defmodule HangmanWeb.GamesChannel do
  use HangmanWeb, :channel

  alias Hangman.Game
  alias Hangman.BackupAgent

  def join("games:" <> name, payload, socket) do
    if authorized?(payload) do
      Hangman.GameServer.start(name)
      game = Hangman.GameServer.peek(name)
      socket = socket
      |> assign(:name, name)
      BackupAgent.put(name, game)
      {:ok, %{"join" => name, "game" => Game.client_view(game)}, socket}
    else
      {:error, %{reason: "unauthorized"}}
    end
  end

  def handle_in("guess", %{"letter" => ll}, socket) do
    name = socket.assigns[:name]
    game = Hangman.GameServer.guess(name, ll)
    {:reply, {:ok, %{ "game" => Game.client_view(game) }}, socket}
  end

  # Add authorization logic here as required.
  defp authorized?(_payload) do
    true
  end
end
