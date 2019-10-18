defmodule LensWeb.PageController do
  use LensWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end
