defmodule HangmanWeb.PageController do
  use HangmanWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end

  def game(conn, _params) do
    render(conn, "game.html")
  end
end
